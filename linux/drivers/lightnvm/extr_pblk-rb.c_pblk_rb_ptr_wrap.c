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
struct pblk_rb {int nr_entries; } ;

/* Variables and functions */

unsigned int pblk_rb_ptr_wrap(struct pblk_rb *rb, unsigned int p,
			      unsigned int nr_entries)
{
	return (p + nr_entries) & (rb->nr_entries - 1);
}