#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int pages_per_area; scalar_t__ nr_areas; int /*<<< orphan*/  lock; int /*<<< orphan*/ ** areas; int /*<<< orphan*/  level; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ debug_info_t ;

/* Variables and functions */
 int NO_AREAS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_1__* debug_info_alloc (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debug_info_free (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static debug_info_t *debug_info_copy(debug_info_t *in, int mode)
{
	unsigned long flags;
	debug_info_t *rc;
	int i, j;

	/* get a consistent copy of the debug areas */
	do {
		rc = debug_info_alloc(in->name, in->pages_per_area,
			in->nr_areas, in->buf_size, in->level, mode);
		spin_lock_irqsave(&in->lock, flags);
		if (!rc)
			goto out;
		/* has something changed in the meantime ? */
		if ((rc->pages_per_area == in->pages_per_area) &&
		    (rc->nr_areas == in->nr_areas)) {
			break;
		}
		spin_unlock_irqrestore(&in->lock, flags);
		debug_info_free(rc);
	} while (1);

	if (mode == NO_AREAS)
		goto out;

	for (i = 0; i < in->nr_areas; i++) {
		for (j = 0; j < in->pages_per_area; j++)
			memcpy(rc->areas[i][j], in->areas[i][j], PAGE_SIZE);
	}
out:
	spin_unlock_irqrestore(&in->lock, flags);
	return rc;
}