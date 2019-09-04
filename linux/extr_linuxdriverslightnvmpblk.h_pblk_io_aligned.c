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
struct pblk {int min_write_pgs; } ;

/* Variables and functions */

__attribute__((used)) static inline int pblk_io_aligned(struct pblk *pblk, int nr_secs)
{
	return !(nr_secs % pblk->min_write_pgs);
}