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
typedef  int u32 ;
struct mdiobb_ctrl {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_mdio_dir ) (struct mdiobb_ctrl*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_C45_ADDR ; 
 int /*<<< orphan*/  mdiobb_cmd (struct mdiobb_ctrl*,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  mdiobb_get_bit (struct mdiobb_ctrl*) ; 
 int /*<<< orphan*/  mdiobb_send_bit (struct mdiobb_ctrl*,int) ; 
 int /*<<< orphan*/  mdiobb_send_num (struct mdiobb_ctrl*,unsigned int,int) ; 
 int /*<<< orphan*/  stub1 (struct mdiobb_ctrl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdiobb_cmd_addr(struct mdiobb_ctrl *ctrl, int phy, u32 addr)
{
	unsigned int dev_addr = (addr >> 16) & 0x1F;
	unsigned int reg = addr & 0xFFFF;
	mdiobb_cmd(ctrl, MDIO_C45_ADDR, phy, dev_addr);

	/* send the turnaround (10) */
	mdiobb_send_bit(ctrl, 1);
	mdiobb_send_bit(ctrl, 0);

	mdiobb_send_num(ctrl, reg, 16);

	ctrl->ops->set_mdio_dir(ctrl, 0);
	mdiobb_get_bit(ctrl);

	return dev_addr;
}