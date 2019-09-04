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
typedef  int u16 ;
struct ice_res_tracker {int search_hint; int* list; int num_entries; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ICE_RES_VALID_BIT ; 

__attribute__((used)) static int ice_search_res(struct ice_res_tracker *res, u16 needed, u16 id)
{
	int start = res->search_hint;
	int end = start;

	id |= ICE_RES_VALID_BIT;

	do {
		/* skip already allocated entries */
		if (res->list[end++] & ICE_RES_VALID_BIT) {
			start = end;
			if ((start + needed) > res->num_entries)
				break;
		}

		if (end == (start + needed)) {
			int i = start;

			/* there was enough, so assign it to the requestor */
			while (i != end)
				res->list[i++] = id;

			if (end == res->num_entries)
				end = 0;

			res->search_hint = end;
			return start;
		}
	} while (1);

	return -ENOMEM;
}