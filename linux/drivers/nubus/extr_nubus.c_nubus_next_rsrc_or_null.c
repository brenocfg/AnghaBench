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
struct nubus_rsrc {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list ; 
 scalar_t__ list_is_last (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nubus_rsrc* list_next_entry (struct nubus_rsrc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nubus_func_rsrcs ; 

struct nubus_rsrc *nubus_next_rsrc_or_null(struct nubus_rsrc *from)
{
	if (list_is_last(&from->list, &nubus_func_rsrcs))
		return NULL;
	return list_next_entry(from, list);
}