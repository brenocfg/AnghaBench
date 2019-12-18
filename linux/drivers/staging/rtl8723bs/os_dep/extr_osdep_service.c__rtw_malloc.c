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

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ in_interrupt () ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *_rtw_malloc(u32 sz)
{
	return kmalloc(sz, in_interrupt() ? GFP_ATOMIC : GFP_KERNEL);
}