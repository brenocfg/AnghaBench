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
struct pblk_w_ctx {int dummy; } ;
struct pblk_rb {int nr_entries; TYPE_1__* entries; } ;
struct TYPE_2__ {struct pblk_w_ctx w_ctx; } ;

/* Variables and functions */

struct pblk_w_ctx *pblk_rb_w_ctx(struct pblk_rb *rb, unsigned int pos)
{
	unsigned int entry = pos & (rb->nr_entries - 1);

	return &rb->entries[entry].w_ctx;
}