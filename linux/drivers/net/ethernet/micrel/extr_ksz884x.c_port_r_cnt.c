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
struct ksz_port_mib {size_t mib_start; size_t cnt_ptr; int /*<<< orphan*/ * counter; int /*<<< orphan*/  dropped; } ;
struct ksz_hw {size_t mib_cnt; struct ksz_port_mib* port_mib; } ;

/* Variables and functions */
 size_t PORT_COUNTER_NUM ; 
 int /*<<< orphan*/  port_r_mib_cnt (struct ksz_hw*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_r_mib_pkt (struct ksz_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int port_r_cnt(struct ksz_hw *hw, int port)
{
	struct ksz_port_mib *mib = &hw->port_mib[port];

	if (mib->mib_start < PORT_COUNTER_NUM)
		while (mib->cnt_ptr < PORT_COUNTER_NUM) {
			port_r_mib_cnt(hw, port, mib->cnt_ptr,
				&mib->counter[mib->cnt_ptr]);
			++mib->cnt_ptr;
		}
	if (hw->mib_cnt > PORT_COUNTER_NUM)
		port_r_mib_pkt(hw, port, mib->dropped,
			&mib->counter[PORT_COUNTER_NUM]);
	mib->cnt_ptr = 0;
	return 0;
}