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
typedef  int /*<<< orphan*/  u64 ;
struct nicvf {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_VF_ENA_W1C ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nicvf_int_type_to_mask (int,int) ; 
 int /*<<< orphan*/  nicvf_reg_write (struct nicvf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void nicvf_disable_intr(struct nicvf *nic, int int_type, int q_idx)
{
	u64 mask = nicvf_int_type_to_mask(int_type, q_idx);

	if (!mask) {
		netdev_dbg(nic->netdev,
			   "Failed to disable interrupt: unknown type\n");
		return;
	}

	nicvf_reg_write(nic, NIC_VF_ENA_W1C, mask);
}