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
typedef  scalar_t__ u16 ;
struct ice_res_tracker {scalar_t__ num_entries; scalar_t__* list; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ICE_RES_VALID_BIT ; 

__attribute__((used)) static int ice_free_res(struct ice_res_tracker *res, u16 index, u16 id)
{
	int count = 0;
	int i;

	if (!res || index >= res->num_entries)
		return -EINVAL;

	id |= ICE_RES_VALID_BIT;
	for (i = index; i < res->num_entries && res->list[i] == id; i++) {
		res->list[i] = 0;
		count++;
	}

	return count;
}