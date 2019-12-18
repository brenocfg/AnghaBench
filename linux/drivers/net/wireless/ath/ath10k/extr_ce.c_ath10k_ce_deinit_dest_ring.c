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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_ce_base_address (struct ath10k*,unsigned int) ; 
 int /*<<< orphan*/  ath10k_ce_dest_ring_base_addr_set (struct ath10k*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_ce_dest_ring_highmark_set (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_ce_dest_ring_size_set (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_ce_deinit_dest_ring(struct ath10k *ar, unsigned int ce_id)
{
	u32 ctrl_addr = ath10k_ce_base_address(ar, ce_id);

	ath10k_ce_dest_ring_base_addr_set(ar, ce_id, 0);
	ath10k_ce_dest_ring_size_set(ar, ctrl_addr, 0);
	ath10k_ce_dest_ring_highmark_set(ar, ctrl_addr, 0);
}