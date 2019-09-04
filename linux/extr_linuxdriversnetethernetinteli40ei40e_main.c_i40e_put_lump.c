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
struct i40e_lump_tracking {int num_entries; int* list; int search_hint; } ;

/* Variables and functions */
 int EINVAL ; 
 int I40E_PILE_VALID_BIT ; 

__attribute__((used)) static int i40e_put_lump(struct i40e_lump_tracking *pile, u16 index, u16 id)
{
	int valid_id = (id | I40E_PILE_VALID_BIT);
	int count = 0;
	int i;

	if (!pile || index >= pile->num_entries)
		return -EINVAL;

	for (i = index;
	     i < pile->num_entries && pile->list[i] == valid_id;
	     i++) {
		pile->list[i] = 0;
		count++;
	}

	if (count && index < pile->search_hint)
		pile->search_hint = index;

	return count;
}