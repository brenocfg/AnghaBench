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
struct slave {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr_len; int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 int MAX_ADDR_LEN ; 
 int /*<<< orphan*/  alb_set_slave_mac_addr (struct slave*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_hw_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alb_swap_mac_addr(struct slave *slave1, struct slave *slave2)
{
	u8 tmp_mac_addr[MAX_ADDR_LEN];

	bond_hw_addr_copy(tmp_mac_addr, slave1->dev->dev_addr,
			  slave1->dev->addr_len);
	alb_set_slave_mac_addr(slave1, slave2->dev->dev_addr,
			       slave2->dev->addr_len);
	alb_set_slave_mac_addr(slave2, tmp_mac_addr,
			       slave1->dev->addr_len);

}