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
struct reciprocal_value {int dummy; } ;
struct TYPE_2__ {int packets_per_slave; struct reciprocal_value reciprocal_packets_per_slave; } ;
struct bonding {int /*<<< orphan*/  rr_tx_counter; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  prandom_u32 () ; 
 int /*<<< orphan*/  reciprocal_divide (int /*<<< orphan*/ ,struct reciprocal_value) ; 

__attribute__((used)) static u32 bond_rr_gen_slave_id(struct bonding *bond)
{
	u32 slave_id;
	struct reciprocal_value reciprocal_packets_per_slave;
	int packets_per_slave = bond->params.packets_per_slave;

	switch (packets_per_slave) {
	case 0:
		slave_id = prandom_u32();
		break;
	case 1:
		slave_id = bond->rr_tx_counter;
		break;
	default:
		reciprocal_packets_per_slave =
			bond->params.reciprocal_packets_per_slave;
		slave_id = reciprocal_divide(bond->rr_tx_counter,
					     reciprocal_packets_per_slave);
		break;
	}
	bond->rr_tx_counter++;

	return slave_id;
}