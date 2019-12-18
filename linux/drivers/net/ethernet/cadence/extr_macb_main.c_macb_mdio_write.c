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
typedef  int u16 ;
struct mii_bus {struct macb* priv; } ;
struct macb {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODE ; 
 int /*<<< orphan*/  DATA ; 
 int MACB_BF (int /*<<< orphan*/ ,int) ; 
 int MACB_MAN_CODE ; 
 int MACB_MAN_SOF ; 
 int MACB_MAN_WRITE ; 
 int /*<<< orphan*/  MAN ; 
 int /*<<< orphan*/  PHYA ; 
 int /*<<< orphan*/  REGA ; 
 int /*<<< orphan*/  RW ; 
 int /*<<< orphan*/  SOF ; 
 int macb_mdio_wait_for_idle (struct macb*) ; 
 int /*<<< orphan*/  macb_writel (struct macb*,int /*<<< orphan*/ ,int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int macb_mdio_write(struct mii_bus *bus, int mii_id, int regnum,
			   u16 value)
{
	struct macb *bp = bus->priv;
	int status;

	status = pm_runtime_get_sync(&bp->pdev->dev);
	if (status < 0)
		goto mdio_pm_exit;

	status = macb_mdio_wait_for_idle(bp);
	if (status < 0)
		goto mdio_write_exit;

	macb_writel(bp, MAN, (MACB_BF(SOF, MACB_MAN_SOF)
			      | MACB_BF(RW, MACB_MAN_WRITE)
			      | MACB_BF(PHYA, mii_id)
			      | MACB_BF(REGA, regnum)
			      | MACB_BF(CODE, MACB_MAN_CODE)
			      | MACB_BF(DATA, value)));

	status = macb_mdio_wait_for_idle(bp);
	if (status < 0)
		goto mdio_write_exit;

mdio_write_exit:
	pm_runtime_mark_last_busy(&bp->pdev->dev);
	pm_runtime_put_autosuspend(&bp->pdev->dev);
mdio_pm_exit:
	return status;
}