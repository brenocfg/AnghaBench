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
struct adapter {TYPE_1__** port; } ;
struct TYPE_2__ {unsigned int mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_MTU_PORT_TABLE ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void init_port_mtus(struct adapter *adapter)
{
	unsigned int mtus = adapter->port[0]->mtu;

	if (adapter->port[1])
		mtus |= adapter->port[1]->mtu << 16;
	t3_write_reg(adapter, A_TP_MTU_PORT_TABLE, mtus);
}