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
 unsigned int* cp1_base ; 
 int /*<<< orphan*/  panic (char*) ; 

unsigned int *ltq_get_cp1_base(void)
{
	if (!cp1_base)
		panic("no cp1 base was set\n");

	return cp1_base;
}