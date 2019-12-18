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
typedef  int u8 ;
struct ksz_device {int port_mask; TYPE_1__* ports; } ;
struct TYPE_2__ {int member; } ;

/* Variables and functions */
 int PORT_VLAN_MEMBERSHIP ; 
 int /*<<< orphan*/  P_MIRROR_CTRL ; 
 int /*<<< orphan*/  ksz_pread8 (struct ksz_device*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ksz_pwrite8 (struct ksz_device*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ksz8795_cfg_port_member(struct ksz_device *dev, int port,
				    u8 member)
{
	u8 data;

	ksz_pread8(dev, port, P_MIRROR_CTRL, &data);
	data &= ~PORT_VLAN_MEMBERSHIP;
	data |= (member & dev->port_mask);
	ksz_pwrite8(dev, port, P_MIRROR_CTRL, data);
	dev->ports[port].member = member;
}