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
struct deflect_struc {struct deflect_struc* next; int /*<<< orphan*/  rule; } ;
typedef  int /*<<< orphan*/  divert_rule ;

/* Variables and functions */
 struct deflect_struc* table_head ; 

divert_rule *getruleptr(int idx)
{
	struct deflect_struc *ds = table_head;

	if (idx < 0) return (NULL);
	while ((ds) && (idx >= 0)) {
		if (!(idx--)) {
			return (&ds->rule);
			break;
		}
		ds = ds->next;
	}
	return (NULL);
}