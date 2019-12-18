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
typedef  int /*<<< orphan*/  u64 ;
struct ksz_port_mib {size_t cnt_ptr; int /*<<< orphan*/ * counters; } ;
struct ksz_device {size_t reg_mib_cnt; size_t mib_cnt; TYPE_2__* dev_ops; TYPE_1__* ports; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* r_mib_pkt ) (struct ksz_device*,int,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* r_mib_cnt ) (struct ksz_device*,int,size_t,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {struct ksz_port_mib mib; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ksz_device*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct ksz_device*,int,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void port_r_cnt(struct ksz_device *dev, int port)
{
	struct ksz_port_mib *mib = &dev->ports[port].mib;
	u64 *dropped;

	/* Some ports may not have MIB counters before SWITCH_COUNTER_NUM. */
	while (mib->cnt_ptr < dev->reg_mib_cnt) {
		dev->dev_ops->r_mib_cnt(dev, port, mib->cnt_ptr,
					&mib->counters[mib->cnt_ptr]);
		++mib->cnt_ptr;
	}

	/* last one in storage */
	dropped = &mib->counters[dev->mib_cnt];

	/* Some ports may not have MIB counters after SWITCH_COUNTER_NUM. */
	while (mib->cnt_ptr < dev->mib_cnt) {
		dev->dev_ops->r_mib_pkt(dev, port, mib->cnt_ptr,
					dropped, &mib->counters[mib->cnt_ptr]);
		++mib->cnt_ptr;
	}
	mib->cnt_ptr = 0;
}