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

/* Variables and functions */
 int addr_in_gen_pool (int /*<<< orphan*/ ,unsigned long,size_t) ; 
 int /*<<< orphan*/  atomic_pool ; 

__attribute__((used)) static bool __in_atomic_pool(void *start, size_t size)
{
	return addr_in_gen_pool(atomic_pool, (unsigned long)start, size);
}