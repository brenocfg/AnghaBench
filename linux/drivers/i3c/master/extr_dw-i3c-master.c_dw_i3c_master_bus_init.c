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
typedef  int u32 ;
struct i3c_master_controller {int dummy; } ;
struct i3c_device_info {int dyn_addr; } ;
struct i3c_bus {int mode; } ;
struct dw_i3c_master {scalar_t__ regs; int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 scalar_t__ DATA_BUFFER_THLD_CTRL ; 
 int DATA_BUFFER_THLD_CTRL_RX_BUF ; 
 scalar_t__ DEVICE_ADDR ; 
 scalar_t__ DEVICE_CTRL ; 
 int DEV_ADDR_DYNAMIC (int) ; 
 int DEV_ADDR_DYNAMIC_ADDR_VALID ; 
 int DEV_CTRL_HOT_JOIN_NACK ; 
 int EINVAL ; 
#define  I3C_BUS_MODE_MIXED_FAST 130 
#define  I3C_BUS_MODE_MIXED_LIMITED 129 
#define  I3C_BUS_MODE_PURE 128 
 scalar_t__ IBI_MR_REQ_REJECT ; 
 int IBI_REQ_REJECT_ALL ; 
 scalar_t__ IBI_SIR_REQ_REJECT ; 
 int INTR_ALL ; 
 int INTR_MASTER_MASK ; 
 scalar_t__ INTR_SIGNAL_EN ; 
 scalar_t__ INTR_STATUS ; 
 scalar_t__ INTR_STATUS_EN ; 
 scalar_t__ QUEUE_THLD_CTRL ; 
 int QUEUE_THLD_CTRL_RESP_BUF_MASK ; 
 int dw_i2c_clk_cfg (struct dw_i3c_master*) ; 
 int dw_i3c_clk_cfg (struct dw_i3c_master*) ; 
 int /*<<< orphan*/  dw_i3c_master_enable (struct dw_i3c_master*) ; 
 struct i3c_bus* i3c_master_get_bus (struct i3c_master_controller*) ; 
 int i3c_master_get_free_addr (struct i3c_master_controller*,int /*<<< orphan*/ ) ; 
 int i3c_master_set_info (int /*<<< orphan*/ *,struct i3c_device_info*) ; 
 int /*<<< orphan*/  memset (struct i3c_device_info*,int /*<<< orphan*/ ,int) ; 
 int readl (scalar_t__) ; 
 struct dw_i3c_master* to_dw_i3c_master (struct i3c_master_controller*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int dw_i3c_master_bus_init(struct i3c_master_controller *m)
{
	struct dw_i3c_master *master = to_dw_i3c_master(m);
	struct i3c_bus *bus = i3c_master_get_bus(m);
	struct i3c_device_info info = { };
	u32 thld_ctrl;
	int ret;

	switch (bus->mode) {
	case I3C_BUS_MODE_MIXED_FAST:
	case I3C_BUS_MODE_MIXED_LIMITED:
		ret = dw_i2c_clk_cfg(master);
		if (ret)
			return ret;
		/* fall through */
	case I3C_BUS_MODE_PURE:
		ret = dw_i3c_clk_cfg(master);
		if (ret)
			return ret;
		break;
	default:
		return -EINVAL;
	}

	thld_ctrl = readl(master->regs + QUEUE_THLD_CTRL);
	thld_ctrl &= ~QUEUE_THLD_CTRL_RESP_BUF_MASK;
	writel(thld_ctrl, master->regs + QUEUE_THLD_CTRL);

	thld_ctrl = readl(master->regs + DATA_BUFFER_THLD_CTRL);
	thld_ctrl &= ~DATA_BUFFER_THLD_CTRL_RX_BUF;
	writel(thld_ctrl, master->regs + DATA_BUFFER_THLD_CTRL);

	writel(INTR_ALL, master->regs + INTR_STATUS);
	writel(INTR_MASTER_MASK, master->regs + INTR_STATUS_EN);
	writel(INTR_MASTER_MASK, master->regs + INTR_SIGNAL_EN);

	ret = i3c_master_get_free_addr(m, 0);
	if (ret < 0)
		return ret;

	writel(DEV_ADDR_DYNAMIC_ADDR_VALID | DEV_ADDR_DYNAMIC(ret),
	       master->regs + DEVICE_ADDR);

	memset(&info, 0, sizeof(info));
	info.dyn_addr = ret;

	ret = i3c_master_set_info(&master->base, &info);
	if (ret)
		return ret;

	writel(IBI_REQ_REJECT_ALL, master->regs + IBI_SIR_REQ_REJECT);
	writel(IBI_REQ_REJECT_ALL, master->regs + IBI_MR_REQ_REJECT);

	/* For now don't support Hot-Join */
	writel(readl(master->regs + DEVICE_CTRL) | DEV_CTRL_HOT_JOIN_NACK,
	       master->regs + DEVICE_CTRL);

	dw_i3c_master_enable(master);

	return 0;
}