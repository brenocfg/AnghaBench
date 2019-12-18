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
 int PAGE_ALIGN (int) ; 
 unsigned long PAGE_MASK ; 
 int PAGE_SHIFT ; 

__attribute__((used)) static u32 hgcm_call_buf_size_in_pages(void *buf, u32 len)
{
	u32 size = PAGE_ALIGN(len + ((unsigned long)buf & ~PAGE_MASK));

	return size >> PAGE_SHIFT;
}