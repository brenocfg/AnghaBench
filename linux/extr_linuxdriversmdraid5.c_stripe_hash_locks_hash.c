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
typedef  int sector_t ;

/* Variables and functions */
 int STRIPE_HASH_LOCKS_MASK ; 
 int STRIPE_SHIFT ; 

__attribute__((used)) static inline int stripe_hash_locks_hash(sector_t sect)
{
	return (sect >> STRIPE_SHIFT) & STRIPE_HASH_LOCKS_MASK;
}