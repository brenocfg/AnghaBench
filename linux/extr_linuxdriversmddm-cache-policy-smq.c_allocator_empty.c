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
struct entry_alloc {int /*<<< orphan*/  free; } ;

/* Variables and functions */
 int l_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool allocator_empty(struct entry_alloc *ea)
{
	return l_empty(&ea->free);
}