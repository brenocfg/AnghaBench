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
 int PGDIR_MASK ; 
 int /*<<< orphan*/  VMALLOC_END ; 
 int VMALLOC_START ; 
 int /*<<< orphan*/  sync_global_pgds (int,int /*<<< orphan*/ ) ; 

void vmalloc_sync_all(void)
{
	sync_global_pgds(VMALLOC_START & PGDIR_MASK, VMALLOC_END);
}