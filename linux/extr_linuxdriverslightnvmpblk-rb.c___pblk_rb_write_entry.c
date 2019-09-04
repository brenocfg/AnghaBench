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
struct pblk_w_ctx {int /*<<< orphan*/  ppa; int /*<<< orphan*/  lba; } ;
struct TYPE_2__ {int /*<<< orphan*/  ppa; int /*<<< orphan*/  lba; } ;
struct pblk_rb_entry {TYPE_1__ w_ctx; int /*<<< orphan*/  data; } ;
struct pblk_rb {int /*<<< orphan*/  seg_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __pblk_rb_write_entry(struct pblk_rb *rb, void *data,
				  struct pblk_w_ctx w_ctx,
				  struct pblk_rb_entry *entry)
{
	memcpy(entry->data, data, rb->seg_size);

	entry->w_ctx.lba = w_ctx.lba;
	entry->w_ctx.ppa = w_ctx.ppa;
}