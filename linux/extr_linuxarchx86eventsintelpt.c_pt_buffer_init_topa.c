#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct topa {int dummy; } ;
struct pt_buffer {unsigned long nr_pages; int /*<<< orphan*/  last; TYPE_1__* first; int /*<<< orphan*/  cpu; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {int base; int end; } ;
struct TYPE_3__ {int phys; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PT_CAP_topa_multiple_entries ; 
 TYPE_2__* TOPA_ENTRY (int /*<<< orphan*/ ,int) ; 
 int TOPA_SHIFT ; 
 int /*<<< orphan*/  pt_buffer_fini_topa (struct pt_buffer*) ; 
 int /*<<< orphan*/  pt_buffer_setup_topa_index (struct pt_buffer*) ; 
 scalar_t__ pt_cap_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_topa_dump (struct pt_buffer*) ; 
 struct topa* topa_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int topa_insert_pages (struct pt_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  topa_insert_table (struct pt_buffer*,struct topa*) ; 

__attribute__((used)) static int pt_buffer_init_topa(struct pt_buffer *buf, unsigned long nr_pages,
			       gfp_t gfp)
{
	struct topa *topa;
	int err;

	topa = topa_alloc(buf->cpu, gfp);
	if (!topa)
		return -ENOMEM;

	topa_insert_table(buf, topa);

	while (buf->nr_pages < nr_pages) {
		err = topa_insert_pages(buf, gfp);
		if (err) {
			pt_buffer_fini_topa(buf);
			return -ENOMEM;
		}
	}

	pt_buffer_setup_topa_index(buf);

	/* link last table to the first one, unless we're double buffering */
	if (pt_cap_get(PT_CAP_topa_multiple_entries)) {
		TOPA_ENTRY(buf->last, -1)->base = buf->first->phys >> TOPA_SHIFT;
		TOPA_ENTRY(buf->last, -1)->end = 1;
	}

	pt_topa_dump(buf);
	return 0;
}