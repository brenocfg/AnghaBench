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
struct hash_pte {int /*<<< orphan*/  v; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPTE_LOCK_BIT ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static inline void native_unlock_hpte(struct hash_pte *hptep)
{
	unsigned long *word = (unsigned long *)&hptep->v;

	clear_bit_unlock(HPTE_LOCK_BIT, word);
}