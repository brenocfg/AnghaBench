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
struct tid_info {unsigned int ntids; void** tid_tab; } ;

/* Variables and functions */

__attribute__((used)) static inline void *lookup_tid(const struct tid_info *t, unsigned int tid)
{
	return tid < t->ntids ? t->tid_tab[tid] : NULL;
}