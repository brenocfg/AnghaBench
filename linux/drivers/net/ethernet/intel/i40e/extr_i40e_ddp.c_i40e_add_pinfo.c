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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct i40e_profile_segment {int /*<<< orphan*/  name; int /*<<< orphan*/  version; } ;
struct TYPE_2__ {int offset; int size; int /*<<< orphan*/  type; } ;
struct i40e_profile_section_header {int tbl_size; int data_end; TYPE_1__ section; } ;
struct i40e_profile_info {int /*<<< orphan*/  name; int /*<<< orphan*/  reserved; int /*<<< orphan*/  op; int /*<<< orphan*/  version; int /*<<< orphan*/  track_id; } ;
struct i40e_hw {int dummy; } ;
typedef  int i40e_status ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_DDP_ADD_TRACKID ; 
 int /*<<< orphan*/  I40E_DDP_NAME_SIZE ; 
 int /*<<< orphan*/  SECTION_TYPE_INFO ; 
 int i40e_aq_write_ddp (struct i40e_hw*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum i40e_status_code
i40e_add_pinfo(struct i40e_hw *hw, struct i40e_profile_segment *profile,
	       u8 *profile_info_sec, u32 track_id)
{
	struct i40e_profile_section_header *sec;
	struct i40e_profile_info *pinfo;
	i40e_status status;
	u32 offset = 0, info = 0;

	sec = (struct i40e_profile_section_header *)profile_info_sec;
	sec->tbl_size = 1;
	sec->data_end = sizeof(struct i40e_profile_section_header) +
			sizeof(struct i40e_profile_info);
	sec->section.type = SECTION_TYPE_INFO;
	sec->section.offset = sizeof(struct i40e_profile_section_header);
	sec->section.size = sizeof(struct i40e_profile_info);
	pinfo = (struct i40e_profile_info *)(profile_info_sec +
					     sec->section.offset);
	pinfo->track_id = track_id;
	pinfo->version = profile->version;
	pinfo->op = I40E_DDP_ADD_TRACKID;

	/* Clear reserved field */
	memset(pinfo->reserved, 0, sizeof(pinfo->reserved));
	memcpy(pinfo->name, profile->name, I40E_DDP_NAME_SIZE);

	status = i40e_aq_write_ddp(hw, (void *)sec, sec->data_end,
				   track_id, &offset, &info, NULL);
	return status;
}