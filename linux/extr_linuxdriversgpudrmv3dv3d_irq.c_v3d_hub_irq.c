#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct v3d_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  V3D_HUB_INT_CLR ; 
 int V3D_HUB_INT_MMU_CAP ; 
 int V3D_HUB_INT_MMU_PTI ; 
 int V3D_HUB_INT_MMU_WRV ; 
 int /*<<< orphan*/  V3D_HUB_INT_STS ; 
 int /*<<< orphan*/  V3D_MMU_VIO_ADDR ; 
 int /*<<< orphan*/  V3D_MMU_VIO_ID ; 
 int V3D_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,long long,char*,char*,char*) ; 

__attribute__((used)) static irqreturn_t
v3d_hub_irq(int irq, void *arg)
{
	struct v3d_dev *v3d = arg;
	u32 intsts;
	irqreturn_t status = IRQ_NONE;

	intsts = V3D_READ(V3D_HUB_INT_STS);

	/* Acknowledge the interrupts we're handling here. */
	V3D_WRITE(V3D_HUB_INT_CLR, intsts);

	if (intsts & (V3D_HUB_INT_MMU_WRV |
		      V3D_HUB_INT_MMU_PTI |
		      V3D_HUB_INT_MMU_CAP)) {
		u32 axi_id = V3D_READ(V3D_MMU_VIO_ID);
		u64 vio_addr = (u64)V3D_READ(V3D_MMU_VIO_ADDR) << 8;

		dev_err(v3d->dev, "MMU error from client %d at 0x%08llx%s%s%s\n",
			axi_id, (long long)vio_addr,
			((intsts & V3D_HUB_INT_MMU_WRV) ?
			 ", write violation" : ""),
			((intsts & V3D_HUB_INT_MMU_PTI) ?
			 ", pte invalid" : ""),
			((intsts & V3D_HUB_INT_MMU_CAP) ?
			 ", cap exceeded" : ""));
		status = IRQ_HANDLED;
	}

	return status;
}