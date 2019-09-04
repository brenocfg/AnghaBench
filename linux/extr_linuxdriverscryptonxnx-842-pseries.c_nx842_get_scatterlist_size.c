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
struct nx842_slentry {int dummy; } ;
struct nx842_scatterlist {int entry_nr; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long nx842_get_scatterlist_size(
				struct nx842_scatterlist *sl)
{
	return sl->entry_nr * sizeof(struct nx842_slentry);
}