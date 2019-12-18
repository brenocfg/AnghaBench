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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (size_t,int /*<<< orphan*/ ) ; 

void lkdtm_OVERWRITE_ALLOCATION(void)
{
	size_t len = 1020;
	u32 *data = kmalloc(len, GFP_KERNEL);
	if (!data)
		return;

	data[1024 / sizeof(u32)] = 0x12345678;
	kfree(data);
}