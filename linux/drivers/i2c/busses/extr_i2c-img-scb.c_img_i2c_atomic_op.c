#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;
struct img_i2c {int at_cur_cmd; int at_cur_data; scalar_t__ mode; int at_t_done; int at_slave_event; scalar_t__ line_status; TYPE_2__ adap; } ;

/* Variables and functions */
 int CMD_GEN_DATA ; 
 int CMD_RET_ACK ; 
 int CMD_RET_DATA ; 
 int LINESTAT_SDAT_LINE_STATUS ; 
 scalar_t__ MODE_ATOMIC ; 
 int /*<<< orphan*/  MODE_RAW ; 
 int OVERRIDE_CMD_MASK ; 
 int OVERRIDE_CMD_SHIFT ; 
 int OVERRIDE_DATA_SHIFT ; 
 int OVERRIDE_DIRECT ; 
 int OVERRIDE_MASTER ; 
 int /*<<< orphan*/  SCB_OVERRIDE_REG ; 
 int /*<<< orphan*/  SCB_STATUS_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  img_i2c_atomic_op_name (int) ; 
 int /*<<< orphan*/  img_i2c_raw_op (struct img_i2c*) ; 
 int img_i2c_readl (struct img_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_i2c_switch_mode (struct img_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_i2c_writel (struct img_i2c*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void img_i2c_atomic_op(struct img_i2c *i2c, int cmd, u8 data)
{
	i2c->at_cur_cmd = cmd;
	i2c->at_cur_data = data;

	/* work around lack of data setup time when generating data */
	if (cmd == CMD_GEN_DATA && i2c->mode == MODE_ATOMIC) {
		u32 line_status = img_i2c_readl(i2c, SCB_STATUS_REG);

		if (line_status & LINESTAT_SDAT_LINE_STATUS && !(data & 0x80)) {
			/* hold the data line down for a moment */
			img_i2c_switch_mode(i2c, MODE_RAW);
			img_i2c_raw_op(i2c);
			return;
		}
	}

	dev_dbg(i2c->adap.dev.parent,
		"atomic cmd=%s (%d) data=%#x\n",
		img_i2c_atomic_op_name(cmd), cmd, data);
	i2c->at_t_done = (cmd == CMD_RET_DATA || cmd == CMD_RET_ACK);
	i2c->at_slave_event = false;
	i2c->line_status = 0;

	img_i2c_writel(i2c, SCB_OVERRIDE_REG,
		((cmd & OVERRIDE_CMD_MASK) << OVERRIDE_CMD_SHIFT) |
		OVERRIDE_MASTER |
		OVERRIDE_DIRECT |
		(data << OVERRIDE_DATA_SHIFT));
}