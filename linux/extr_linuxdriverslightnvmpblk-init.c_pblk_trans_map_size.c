#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int nr_secs; } ;
struct pblk {int addrf_len; TYPE_1__ rl; } ;

/* Variables and functions */

__attribute__((used)) static size_t pblk_trans_map_size(struct pblk *pblk)
{
	int entry_size = 8;

	if (pblk->addrf_len < 32)
		entry_size = 4;

	return entry_size * pblk->rl.nr_secs;
}