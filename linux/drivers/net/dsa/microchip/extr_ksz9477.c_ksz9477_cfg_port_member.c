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
typedef  int /*<<< orphan*/  u8 ;
struct ksz_device {TYPE_1__* ports; } ;
struct TYPE_2__ {int /*<<< orphan*/  member; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_PORT_VLAN_MEMBERSHIP__4 ; 
 int /*<<< orphan*/  ksz_pwrite32 (struct ksz_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ksz9477_cfg_port_member(struct ksz_device *dev, int port,
				    u8 member)
{
	ksz_pwrite32(dev, port, REG_PORT_VLAN_MEMBERSHIP__4, member);
	dev->ports[port].member = member;
}