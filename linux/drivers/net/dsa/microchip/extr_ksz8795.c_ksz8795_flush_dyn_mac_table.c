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
typedef  int uint ;
typedef  int u8 ;
struct ksz_port {int /*<<< orphan*/  on; } ;
struct ksz_device {int mib_port_cnt; struct ksz_port* ports; } ;

/* Variables and functions */
 int PORT_LEARN_DISABLE ; 
 int /*<<< orphan*/  P_STP_CTRL ; 
 int /*<<< orphan*/  SW_FLUSH_DYN_MAC_TABLE ; 
 int /*<<< orphan*/  S_FLUSH_TABLE_CTRL ; 
 int TOTAL_PORT_NUM ; 
 int /*<<< orphan*/  ksz_cfg (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ksz_pread8 (struct ksz_device*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ksz_pwrite8 (struct ksz_device*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ksz8795_flush_dyn_mac_table(struct ksz_device *dev, int port)
{
	u8 learn[TOTAL_PORT_NUM];
	int first, index, cnt;
	struct ksz_port *p;

	if ((uint)port < TOTAL_PORT_NUM) {
		first = port;
		cnt = port + 1;
	} else {
		/* Flush all ports. */
		first = 0;
		cnt = dev->mib_port_cnt;
	}
	for (index = first; index < cnt; index++) {
		p = &dev->ports[index];
		if (!p->on)
			continue;
		ksz_pread8(dev, index, P_STP_CTRL, &learn[index]);
		if (!(learn[index] & PORT_LEARN_DISABLE))
			ksz_pwrite8(dev, index, P_STP_CTRL,
				    learn[index] | PORT_LEARN_DISABLE);
	}
	ksz_cfg(dev, S_FLUSH_TABLE_CTRL, SW_FLUSH_DYN_MAC_TABLE, true);
	for (index = first; index < cnt; index++) {
		p = &dev->ports[index];
		if (!p->on)
			continue;
		if (!(learn[index] & PORT_LEARN_DISABLE))
			ksz_pwrite8(dev, index, P_STP_CTRL, learn[index]);
	}
}