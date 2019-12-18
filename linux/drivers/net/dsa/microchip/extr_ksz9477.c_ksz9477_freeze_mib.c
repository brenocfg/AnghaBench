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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  cnt_mutex; } ;
struct ksz_port {int freeze; TYPE_1__ mib; } ;
struct ksz_device {struct ksz_port* ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIB_COUNTER_FLUSH_FREEZE ; 
 int /*<<< orphan*/  REG_PORT_MIB_CTRL_STAT__4 ; 
 int /*<<< orphan*/  ksz_pwrite32 (struct ksz_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ksz9477_freeze_mib(struct ksz_device *dev, int port, bool freeze)
{
	u32 val = freeze ? MIB_COUNTER_FLUSH_FREEZE : 0;
	struct ksz_port *p = &dev->ports[port];

	/* enable/disable the port for flush/freeze function */
	mutex_lock(&p->mib.cnt_mutex);
	ksz_pwrite32(dev, port, REG_PORT_MIB_CTRL_STAT__4, val);

	/* used by MIB counter reading code to know freeze is enabled */
	p->freeze = freeze;
	mutex_unlock(&p->mib.cnt_mutex);
}