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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u64 ;
struct ksz_port_mib {int /*<<< orphan*/  cnt_mutex; int /*<<< orphan*/  counters; int /*<<< orphan*/  cnt_ptr; } ;
struct ksz_device {int mib_cnt; int /*<<< orphan*/  reg_mib_cnt; TYPE_1__* ports; } ;
struct dsa_switch {struct ksz_device* priv; } ;
struct dsa_port {int /*<<< orphan*/  slave; } ;
struct TYPE_2__ {struct ksz_port_mib mib; } ;

/* Variables and functions */
 struct dsa_port* dsa_to_port (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_r_cnt (struct ksz_device*,int) ; 

void ksz_get_ethtool_stats(struct dsa_switch *ds, int port, uint64_t *buf)
{
	const struct dsa_port *dp = dsa_to_port(ds, port);
	struct ksz_device *dev = ds->priv;
	struct ksz_port_mib *mib;

	mib = &dev->ports[port].mib;
	mutex_lock(&mib->cnt_mutex);

	/* Only read dropped counters if no link. */
	if (!netif_carrier_ok(dp->slave))
		mib->cnt_ptr = dev->reg_mib_cnt;
	port_r_cnt(dev, port);
	memcpy(buf, mib->counters, dev->mib_cnt * sizeof(u64));
	mutex_unlock(&mib->cnt_mutex);
}