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
struct i40e_tx_desc {int dummy; } ;
struct i40e_ring {int count; scalar_t__ desc; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/  volatile) ; 

__attribute__((used)) static inline u32 i40e_get_head(struct i40e_ring *tx_ring)
{
	void *head = (struct i40e_tx_desc *)tx_ring->desc + tx_ring->count;

	return le32_to_cpu(*(volatile __le32 *)head);
}