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
struct vm_area_struct {int dummy; } ;
struct flusher_data {unsigned long addr1; unsigned long addr2; struct vm_area_struct* vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  cacheop_on_each_cpu (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  local_flush_cache_range ; 

void flush_cache_range(struct vm_area_struct *vma, unsigned long start,
		       unsigned long end)
{
	struct flusher_data data;

	data.vma = vma;
	data.addr1 = start;
	data.addr2 = end;

	cacheop_on_each_cpu(local_flush_cache_range, (void *)&data, 1);
}