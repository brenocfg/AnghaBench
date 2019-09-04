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
struct __cache {int init_tag_val; int no_ops; int read_addr; int read_addr_num; scalar_t__ stride; scalar_t__ read_addr_stride; int /*<<< orphan*/  ctrl_val; int /*<<< orphan*/  ctrl_addr; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {struct __cache cache; } ;
struct qlcnic_dump_entry {TYPE_1__ region; } ;
struct qlcnic_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int LSW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int qlcnic_ind_rd (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_ind_wr (struct qlcnic_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 qlcnic_dump_l1_cache(struct qlcnic_adapter *adapter,
				struct qlcnic_dump_entry *entry, __le32 *buffer)
{
	int i;
	u32 cnt, val, data, addr;
	struct __cache *l1 = &entry->region.cache;

	val = l1->init_tag_val;

	for (i = 0; i < l1->no_ops; i++) {
		qlcnic_ind_wr(adapter, l1->addr, val);
		qlcnic_ind_wr(adapter, l1->ctrl_addr, LSW(l1->ctrl_val));
		addr = l1->read_addr;
		cnt = l1->read_addr_num;
		while (cnt) {
			data = qlcnic_ind_rd(adapter, addr);
			*buffer++ = cpu_to_le32(data);
			addr += l1->read_addr_stride;
			cnt--;
		}
		val += l1->stride;
	}
	return l1->no_ops * l1->read_addr_num * sizeof(u32);
}