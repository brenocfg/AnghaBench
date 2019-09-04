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
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_HEAD (struct hlist_head*) ; 

__attribute__((used)) static void kvmppc_mmu_hpte_init_hash(struct hlist_head *hash_list, int len)
{
	int i;

	for (i = 0; i < len; i++)
		INIT_HLIST_HEAD(&hash_list[i]);
}