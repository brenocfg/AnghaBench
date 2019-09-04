#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct mii_bus {struct fec_enet_private* priv; } ;
struct fec_enet_private {int mii_timeout; int /*<<< orphan*/  netdev; int /*<<< orphan*/  mdio_done; scalar_t__ hwp; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ FEC_MII_DATA ; 
 int /*<<< orphan*/  FEC_MII_TIMEOUT ; 
 int FEC_MMFR_DATA (int /*<<< orphan*/ ) ; 
 int FEC_MMFR_OP_WRITE ; 
 int FEC_MMFR_PA (int) ; 
 int FEC_MMFR_RA (int) ; 
 int FEC_MMFR_ST ; 
 int FEC_MMFR_TA ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int /*<<< orphan*/ ) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int fec_enet_mdio_write(struct mii_bus *bus, int mii_id, int regnum,
			   u16 value)
{
	struct fec_enet_private *fep = bus->priv;
	struct device *dev = &fep->pdev->dev;
	unsigned long time_left;
	int ret;

	ret = pm_runtime_get_sync(dev);
	if (ret < 0)
		return ret;
	else
		ret = 0;

	fep->mii_timeout = 0;
	reinit_completion(&fep->mdio_done);

	/* start a write op */
	writel(FEC_MMFR_ST | FEC_MMFR_OP_WRITE |
		FEC_MMFR_PA(mii_id) | FEC_MMFR_RA(regnum) |
		FEC_MMFR_TA | FEC_MMFR_DATA(value),
		fep->hwp + FEC_MII_DATA);

	/* wait for end of transfer */
	time_left = wait_for_completion_timeout(&fep->mdio_done,
			usecs_to_jiffies(FEC_MII_TIMEOUT));
	if (time_left == 0) {
		fep->mii_timeout = 1;
		netdev_err(fep->netdev, "MDIO write timeout\n");
		ret  = -ETIMEDOUT;
	}

	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);

	return ret;
}