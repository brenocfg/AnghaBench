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
struct __mux {int val; int no_ops; scalar_t__ val_stride; int /*<<< orphan*/  read_addr; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {struct __mux mux; } ;
struct qlcnic_dump_entry {TYPE_1__ region; } ;
struct qlcnic_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 void* cpu_to_le32 (int) ; 
 int qlcnic_ind_rd (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_ind_wr (struct qlcnic_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 qlcnic_dump_mux(struct qlcnic_adapter *adapter,
			   struct qlcnic_dump_entry *entry, __le32 *buffer)
{
	int loop;
	u32 val, data = 0;
	struct __mux *mux = &entry->region.mux;

	val = mux->val;
	for (loop = 0; loop < mux->no_ops; loop++) {
		qlcnic_ind_wr(adapter, mux->addr, val);
		data = qlcnic_ind_rd(adapter, mux->read_addr);
		*buffer++ = cpu_to_le32(val);
		*buffer++ = cpu_to_le32(data);
		val += mux->val_stride;
	}
	return 2 * mux->no_ops * sizeof(u32);
}