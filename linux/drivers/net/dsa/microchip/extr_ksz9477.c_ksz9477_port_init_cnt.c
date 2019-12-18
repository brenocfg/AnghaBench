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
typedef  int /*<<< orphan*/  u64 ;
struct ksz_port_mib {int /*<<< orphan*/  counters; scalar_t__ cnt_ptr; int /*<<< orphan*/  cnt_mutex; } ;
struct ksz_device {int mib_cnt; TYPE_1__* ports; } ;
struct TYPE_2__ {struct ksz_port_mib mib; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIB_COUNTER_FLUSH_FREEZE ; 
 int /*<<< orphan*/  REG_PORT_MIB_CTRL_STAT__4 ; 
 int /*<<< orphan*/  REG_SW_MAC_CTRL_6 ; 
 int /*<<< orphan*/  SW_MIB_COUNTER_FLUSH ; 
 int /*<<< orphan*/  ksz_pwrite32 (struct ksz_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksz_write8 (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ksz9477_port_init_cnt(struct ksz_device *dev, int port)
{
	struct ksz_port_mib *mib = &dev->ports[port].mib;

	/* flush all enabled port MIB counters */
	mutex_lock(&mib->cnt_mutex);
	ksz_pwrite32(dev, port, REG_PORT_MIB_CTRL_STAT__4,
		     MIB_COUNTER_FLUSH_FREEZE);
	ksz_write8(dev, REG_SW_MAC_CTRL_6, SW_MIB_COUNTER_FLUSH);
	ksz_pwrite32(dev, port, REG_PORT_MIB_CTRL_STAT__4, 0);
	mutex_unlock(&mib->cnt_mutex);

	mib->cnt_ptr = 0;
	memset(mib->counters, 0, dev->mib_cnt * sizeof(u64));
}