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
struct topa_entry {int dummy; } ;
struct pt_buffer {int nr_pages; struct topa_entry** topa_index; TYPE_1__* first; TYPE_1__* last; } ;
struct TYPE_2__ {int last; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int pt_topa_next_entry(struct pt_buffer *buf, unsigned int pg)
{
	struct topa_entry *te = buf->topa_index[pg];

	/* one region */
	if (buf->first == buf->last && buf->first->last == 1)
		return pg;

	do {
		pg++;
		pg &= buf->nr_pages - 1;
	} while (buf->topa_index[pg] == te);

	return pg;
}