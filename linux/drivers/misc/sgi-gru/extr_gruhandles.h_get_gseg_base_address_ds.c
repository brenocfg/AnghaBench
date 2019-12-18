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
 int GRU_CACHE_LINE_BYTES ; 
 scalar_t__ GRU_DS_BASE ; 
 scalar_t__ get_gseg_base_address (void*,int) ; 

__attribute__((used)) static inline void *get_gseg_base_address_ds(void *base, int ctxnum, int line)
{
	return (void *)(get_gseg_base_address(base, ctxnum) + GRU_DS_BASE +
			GRU_CACHE_LINE_BYTES * line);
}