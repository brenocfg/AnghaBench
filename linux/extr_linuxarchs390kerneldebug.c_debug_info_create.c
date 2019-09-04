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
typedef  int umode_t ;
struct TYPE_6__ {int mode; int /*<<< orphan*/  ref_count; struct TYPE_6__* next; struct TYPE_6__* prev; int /*<<< orphan*/  name; int /*<<< orphan*/  debugfs_root_entry; } ;
typedef  TYPE_1__ debug_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_AREAS ; 
 int /*<<< orphan*/  DEBUG_DEFAULT_LEVEL ; 
 int S_IFMT ; 
 TYPE_1__* debug_area_first ; 
 TYPE_1__* debug_area_last ; 
 int /*<<< orphan*/  debug_debugfs_root_entry ; 
 TYPE_1__* debug_info_alloc (char const*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static debug_info_t *debug_info_create(const char *name, int pages_per_area,
				       int nr_areas, int buf_size, umode_t mode)
{
	debug_info_t *rc;

	rc = debug_info_alloc(name, pages_per_area, nr_areas, buf_size,
			      DEBUG_DEFAULT_LEVEL, ALL_AREAS);
	if (!rc)
		goto out;

	rc->mode = mode & ~S_IFMT;

	/* create root directory */
	rc->debugfs_root_entry = debugfs_create_dir(rc->name,
						    debug_debugfs_root_entry);

	/* append new element to linked list */
	if (!debug_area_first) {
		/* first element in list */
		debug_area_first = rc;
		rc->prev = NULL;
	} else {
		/* append element to end of list */
		debug_area_last->next = rc;
		rc->prev = debug_area_last;
	}
	debug_area_last = rc;
	rc->next = NULL;

	refcount_set(&rc->ref_count, 1);
out:
	return rc;
}