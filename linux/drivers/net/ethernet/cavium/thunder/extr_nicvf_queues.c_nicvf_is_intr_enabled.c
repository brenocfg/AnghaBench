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
typedef  int u64 ;
struct nicvf {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_VF_ENA_W1S ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int nicvf_int_type_to_mask (int,int) ; 
 int nicvf_reg_read (struct nicvf*,int /*<<< orphan*/ ) ; 

int nicvf_is_intr_enabled(struct nicvf *nic, int int_type, int q_idx)
{
	u64 mask = nicvf_int_type_to_mask(int_type, q_idx);
	/* If interrupt type is unknown, we treat it disabled. */
	if (!mask) {
		netdev_dbg(nic->netdev,
			   "Failed to check interrupt enable: unknown type\n");
		return 0;
	}

	return mask & nicvf_reg_read(nic, NIC_VF_ENA_W1S);
}