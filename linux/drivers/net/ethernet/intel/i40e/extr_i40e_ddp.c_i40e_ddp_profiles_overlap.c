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
typedef  unsigned int u8 ;
struct i40e_profile_info {int track_id; } ;

/* Variables and functions */

__attribute__((used)) static bool i40e_ddp_profiles_overlap(struct i40e_profile_info *new,
				      struct i40e_profile_info *old)
{
	unsigned int group_id_old = (u8)((old->track_id & 0x00FF0000) >> 16);
	unsigned int group_id_new = (u8)((new->track_id & 0x00FF0000) >> 16);

	/* 0x00 group must be only the first */
	if (group_id_new == 0)
		return true;
	/* 0xFF group is compatible with anything else */
	if (group_id_new == 0xFF || group_id_old == 0xFF)
		return false;
	/* otherwise only profiles from the same group are compatible*/
	return group_id_old != group_id_new;
}