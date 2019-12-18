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
 int GRU_DS_BASE ; 

__attribute__((used)) static inline void *gru_get_data_pointer(void *gseg, int index)
{
	return gseg + GRU_DS_BASE + index * GRU_CACHE_LINE_BYTES;
}