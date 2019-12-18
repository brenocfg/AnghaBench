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
typedef  int /*<<< orphan*/  atomic_t ;
typedef  int __u32 ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void pvrdma_idx_ring_inc(atomic_t *var, __u32 max_elems)
{
	__u32 idx = atomic_read(var) + 1;	/* Increment. */

	idx &= (max_elems << 1) - 1;		/* Modulo size, flip gen. */
	atomic_set(var, idx);
}