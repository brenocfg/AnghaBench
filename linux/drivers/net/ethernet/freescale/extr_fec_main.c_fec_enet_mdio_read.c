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
struct mii_bus {struct fec_enet_private* priv; } ;
struct fec_enet_private {scalar_t__ hwp; int /*<<< orphan*/  netdev; int /*<<< orphan*/  mdio_done; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ FEC_MII_DATA ; 
 int /*<<< orphan*/  FEC_MII_TIMEOUT ; 
 int FEC_MMFR_DATA (int /*<<< orphan*/ ) ; 
 int FEC_MMFR_OP_ADDR_WRITE ; 
 int FEC_MMFR_OP_READ ; 
 int FEC_MMFR_OP_READ_C45 ; 
 int FEC_MMFR_PA (int) ; 
 int FEC_MMFR_RA (int) ; 
 int FEC_MMFR_ST ; 
 int FEC_MMFR_ST_C45 ; 
 int FEC_MMFR_TA ; 
 int MII_ADDR_C45 ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int /*<<< orphan*/ ) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int fec_enet_mdio_read(struct mii_bus *bus, int mii_id, int regnum)
{
	struct fec_enet_private *fep = bus->priv;
	struct device *dev = &fep->pdev->dev;
	unsigned long time_left;
	int ret = 0, frame_start, frame_addr, frame_op;
	bool is_c45 = !!(regnum & MII_ADDR_C45);

	ret = pm_runtime_get_sync(dev);
	if (ret < 0)
		return ret;

	reinit_completion(&fep->mdio_done);

	if (is_c45) {
		frame_start = FEC_MMFR_ST_C45;

		/* write address */
		frame_addr = (regnum >> 16);
		writel(frame_start | FEC_MMFR_OP_ADDR_WRITE |
		       FEC_MMFR_PA(mii_id) | FEC_MMFR_RA(frame_addr) |
		       FEC_MMFR_TA | (regnum & 0xFFFF),
		       fep->hwp + FEC_MII_DATA);

		/* wait for end of transfer */
		time_left = wait_for_completion_timeout(&fep->mdio_done,
				usecs_to_jiffies(FEC_MII_TIMEOUT));
		if (time_left == 0) {
			netdev_err(fep->netdev, "MDIO address write timeout\n");
			ret = -ETIMEDOUT;
			goto out;
		}

		frame_op = FEC_MMFR_OP_READ_C45;

	} else {
		/* C22 read */
		frame_op = FEC_MMFR_OP_READ;
		frame_start = FEC_MMFR_ST;
		frame_addr = regnum;
	}

	/* start a read op */
	writel(frame_start | frame_op |
		FEC_MMFR_PA(mii_id) | FEC_MMFR_RA(frame_addr) |
		FEC_MMFR_TA, fep->hwp + FEC_MII_DATA);

	/* wait for end of transfer */
	time_left = wait_for_completion_timeout(&fep->mdio_done,
			usecs_to_jiffies(FEC_MII_TIMEOUT));
	if (time_left == 0) {
		netdev_err(fep->netdev, "MDIO read timeout\n");
		ret = -ETIMEDOUT;
		goto out;
	}

	ret = FEC_MMFR_DATA(readl(fep->hwp + FEC_MII_DATA));

out:
	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);

	return ret;
}