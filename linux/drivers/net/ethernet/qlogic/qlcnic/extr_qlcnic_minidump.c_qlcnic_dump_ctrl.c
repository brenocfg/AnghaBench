#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct __ctrl {int addr; int no_ops; int opcode; int val1; int val2; int val3; int timeout; int index_a; int index_v; int shl_val; int shr_val; scalar_t__ stride; } ;
struct TYPE_7__ {struct __ctrl ctrl; } ;
struct qlcnic_dump_entry {TYPE_3__ region; } ;
struct qlcnic_adapter {TYPE_4__* pdev; TYPE_2__* ahw; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {void* tmpl_hdr; } ;
struct TYPE_6__ {TYPE_1__ fw_dump; } ;

/* Variables and functions */
 int EINVAL ; 
#define  QLCNIC_DUMP_ANDCRB 135 
#define  QLCNIC_DUMP_MOD_SAVE_ST 134 
#define  QLCNIC_DUMP_ORCRB 133 
#define  QLCNIC_DUMP_POLLCRB 132 
#define  QLCNIC_DUMP_RD_SAVE 131 
#define  QLCNIC_DUMP_RWCRB 130 
#define  QLCNIC_DUMP_WCRB 129 
#define  QLCNIC_DUMP_WRT_SAVED 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int qlcnic_get_saved_state (struct qlcnic_adapter*,void*,int) ; 
 int qlcnic_ind_rd (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_ind_wr (struct qlcnic_adapter*,int,int) ; 
 int /*<<< orphan*/  qlcnic_set_saved_state (struct qlcnic_adapter*,void*,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static u32 qlcnic_dump_ctrl(struct qlcnic_adapter *adapter,
			    struct qlcnic_dump_entry *entry, __le32 *buffer)
{
	void *hdr = adapter->ahw->fw_dump.tmpl_hdr;
	struct __ctrl *ctr = &entry->region.ctrl;
	int i, k, timeout = 0;
	u32 addr, data, temp;
	u8 no_ops;

	addr = ctr->addr;
	no_ops = ctr->no_ops;

	for (i = 0; i < no_ops; i++) {
		k = 0;
		for (k = 0; k < 8; k++) {
			if (!(ctr->opcode & (1 << k)))
				continue;
			switch (1 << k) {
			case QLCNIC_DUMP_WCRB:
				qlcnic_ind_wr(adapter, addr, ctr->val1);
				break;
			case QLCNIC_DUMP_RWCRB:
				data = qlcnic_ind_rd(adapter, addr);
				qlcnic_ind_wr(adapter, addr, data);
				break;
			case QLCNIC_DUMP_ANDCRB:
				data = qlcnic_ind_rd(adapter, addr);
				qlcnic_ind_wr(adapter, addr,
					      (data & ctr->val2));
				break;
			case QLCNIC_DUMP_ORCRB:
				data = qlcnic_ind_rd(adapter, addr);
				qlcnic_ind_wr(adapter, addr,
					      (data | ctr->val3));
				break;
			case QLCNIC_DUMP_POLLCRB:
				while (timeout <= ctr->timeout) {
					data = qlcnic_ind_rd(adapter, addr);
					if ((data & ctr->val2) == ctr->val1)
						break;
					usleep_range(1000, 2000);
					timeout++;
				}
				if (timeout > ctr->timeout) {
					dev_info(&adapter->pdev->dev,
					"Timed out, aborting poll CRB\n");
					return -EINVAL;
				}
				break;
			case QLCNIC_DUMP_RD_SAVE:
				temp = ctr->index_a;
				if (temp)
					addr = qlcnic_get_saved_state(adapter,
								      hdr,
								      temp);
				data = qlcnic_ind_rd(adapter, addr);
				qlcnic_set_saved_state(adapter, hdr,
						       ctr->index_v, data);
				break;
			case QLCNIC_DUMP_WRT_SAVED:
				temp = ctr->index_v;
				if (temp)
					data = qlcnic_get_saved_state(adapter,
								      hdr,
								      temp);
				else
					data = ctr->val1;

				temp = ctr->index_a;
				if (temp)
					addr = qlcnic_get_saved_state(adapter,
								      hdr,
								      temp);
				qlcnic_ind_wr(adapter, addr, data);
				break;
			case QLCNIC_DUMP_MOD_SAVE_ST:
				data = qlcnic_get_saved_state(adapter, hdr,
							      ctr->index_v);
				data <<= ctr->shl_val;
				data >>= ctr->shr_val;
				if (ctr->val2)
					data &= ctr->val2;
				data |= ctr->val3;
				data += ctr->val1;
				qlcnic_set_saved_state(adapter, hdr,
						       ctr->index_v, data);
				break;
			default:
				dev_info(&adapter->pdev->dev,
					 "Unknown opcode\n");
				break;
			}
		}
		addr += ctr->stride;
	}
	return 0;
}