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
struct dsaf_device {int reset_offset; int /*<<< orphan*/  dsaf_ver; TYPE_1__** mac_cb; } ;
struct TYPE_2__ {int port_rst_off; } ;

/* Variables and functions */
 scalar_t__ AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 int DSAF_GE_NUM ; 
 int /*<<< orphan*/  DSAF_SUB_SC_GE_RESET_DREQ0_REG ; 
 int /*<<< orphan*/  DSAF_SUB_SC_GE_RESET_DREQ1_REG ; 
 int /*<<< orphan*/  DSAF_SUB_SC_GE_RESET_REQ0_REG ; 
 int /*<<< orphan*/  DSAF_SUB_SC_GE_RESET_REQ1_REG ; 
 int /*<<< orphan*/  DSAF_SUB_SC_PPE_RESET_DREQ_REG ; 
 int /*<<< orphan*/  DSAF_SUB_SC_PPE_RESET_REQ_REG ; 
 int /*<<< orphan*/  HNS_DSAF_IS_DEBUG (struct dsaf_device*) ; 
 int /*<<< orphan*/  dsaf_write_sub (struct dsaf_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns_dsaf_ge_srst_by_port(struct dsaf_device *dsaf_dev, u32 port,
				     bool dereset)
{
	u32 reg_val_1;
	u32 reg_val_2;
	u32 port_rst_off;

	if (port >= DSAF_GE_NUM)
		return;

	if (!HNS_DSAF_IS_DEBUG(dsaf_dev)) {
		reg_val_1  = 0x1 << port;
		port_rst_off = dsaf_dev->mac_cb[port]->port_rst_off;
		/* there is difference between V1 and V2 in register.*/
		reg_val_2 = AE_IS_VER1(dsaf_dev->dsaf_ver) ?
				0x1041041 : 0x2082082;
		reg_val_2 <<= port_rst_off;

		if (!dereset) {
			dsaf_write_sub(dsaf_dev, DSAF_SUB_SC_GE_RESET_REQ1_REG,
				       reg_val_1);

			dsaf_write_sub(dsaf_dev, DSAF_SUB_SC_GE_RESET_REQ0_REG,
				       reg_val_2);
		} else {
			dsaf_write_sub(dsaf_dev, DSAF_SUB_SC_GE_RESET_DREQ0_REG,
				       reg_val_2);

			dsaf_write_sub(dsaf_dev, DSAF_SUB_SC_GE_RESET_DREQ1_REG,
				       reg_val_1);
		}
	} else {
		reg_val_1 = 0x15540;
		reg_val_2 = AE_IS_VER1(dsaf_dev->dsaf_ver) ? 0x100 : 0x40;

		reg_val_1 <<= dsaf_dev->reset_offset;
		reg_val_2 <<= dsaf_dev->reset_offset;

		if (!dereset) {
			dsaf_write_sub(dsaf_dev, DSAF_SUB_SC_GE_RESET_REQ1_REG,
				       reg_val_1);

			dsaf_write_sub(dsaf_dev, DSAF_SUB_SC_PPE_RESET_REQ_REG,
				       reg_val_2);
		} else {
			dsaf_write_sub(dsaf_dev, DSAF_SUB_SC_GE_RESET_DREQ1_REG,
				       reg_val_1);

			dsaf_write_sub(dsaf_dev, DSAF_SUB_SC_PPE_RESET_DREQ_REG,
				       reg_val_2);
		}
	}
}