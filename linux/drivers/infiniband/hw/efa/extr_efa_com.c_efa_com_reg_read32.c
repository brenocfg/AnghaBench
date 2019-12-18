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
typedef  int u16 ;
struct efa_com_mmio_read {int seq_num; int /*<<< orphan*/  lock; int /*<<< orphan*/  mmio_read_timeout; struct efa_admin_mmio_req_read_less_resp* read_resp; } ;
struct efa_com_dev {int /*<<< orphan*/  efa_dev; scalar_t__ reg_bar; struct efa_com_mmio_read mmio_read; } ;
struct efa_admin_mmio_req_read_less_resp {int req_id; int reg_off; int reg_val; } ;

/* Variables and functions */
 int EFA_MMIO_READ_INVALID ; 
 scalar_t__ EFA_REGS_MMIO_REG_READ_OFF ; 
 int EFA_REGS_MMIO_REG_READ_REG_OFF_MASK ; 
 int EFA_REGS_MMIO_REG_READ_REG_OFF_SHIFT ; 
 int EFA_REGS_MMIO_REG_READ_REQ_ID_MASK ; 
 int READ_ONCE (int) ; 
 int /*<<< orphan*/  ibdev_err_ratelimited (int /*<<< orphan*/ ,char*,...) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_is_after_jiffies (unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 unsigned long usecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static u32 efa_com_reg_read32(struct efa_com_dev *edev, u16 offset)
{
	struct efa_com_mmio_read *mmio_read = &edev->mmio_read;
	struct efa_admin_mmio_req_read_less_resp *read_resp;
	unsigned long exp_time;
	u32 mmio_read_reg;
	u32 err;

	read_resp = mmio_read->read_resp;

	spin_lock(&mmio_read->lock);
	mmio_read->seq_num++;

	/* trash DMA req_id to identify when hardware is done */
	read_resp->req_id = mmio_read->seq_num + 0x9aL;
	mmio_read_reg = (offset << EFA_REGS_MMIO_REG_READ_REG_OFF_SHIFT) &
			EFA_REGS_MMIO_REG_READ_REG_OFF_MASK;
	mmio_read_reg |= mmio_read->seq_num &
			 EFA_REGS_MMIO_REG_READ_REQ_ID_MASK;

	writel(mmio_read_reg, edev->reg_bar + EFA_REGS_MMIO_REG_READ_OFF);

	exp_time = jiffies + usecs_to_jiffies(mmio_read->mmio_read_timeout);
	do {
		if (READ_ONCE(read_resp->req_id) == mmio_read->seq_num)
			break;
		udelay(1);
	} while (time_is_after_jiffies(exp_time));

	if (read_resp->req_id != mmio_read->seq_num) {
		ibdev_err_ratelimited(
			edev->efa_dev,
			"Reading register timed out. expected: req id[%u] offset[%#x] actual: req id[%u] offset[%#x]\n",
			mmio_read->seq_num, offset, read_resp->req_id,
			read_resp->reg_off);
		err = EFA_MMIO_READ_INVALID;
		goto out;
	}

	if (read_resp->reg_off != offset) {
		ibdev_err_ratelimited(
			edev->efa_dev,
			"Reading register failed: wrong offset provided\n");
		err = EFA_MMIO_READ_INVALID;
		goto out;
	}

	err = read_resp->reg_val;
out:
	spin_unlock(&mmio_read->lock);
	return err;
}