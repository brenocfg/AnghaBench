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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct atom_context {scalar_t__ bios; } ;
struct amdgpu_mode_info {struct atom_context* atom_context; } ;
struct amdgpu_device {struct amdgpu_mode_info mode_info; } ;
struct TYPE_4__ {scalar_t__ ucNumOfDispPath; } ;
struct TYPE_3__ {int /*<<< orphan*/  usDisplayPathTableOffset; } ;
typedef  TYPE_1__ ATOM_OBJECT_HEADER ;
typedef  TYPE_2__ ATOM_DISPLAY_OBJECT_PATH_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Object_Header ; 
 int /*<<< orphan*/  amdgpu_atom_parse_data_header (struct atom_context*,int,scalar_t__*,int*,int*,scalar_t__*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

bool amdgpu_atombios_has_dce_engine_info(struct amdgpu_device *adev)
{
	struct amdgpu_mode_info *mode_info = &adev->mode_info;
	struct atom_context *ctx = mode_info->atom_context;
	int index = GetIndexIntoMasterTable(DATA, Object_Header);
	u16 size, data_offset;
	u8 frev, crev;
	ATOM_DISPLAY_OBJECT_PATH_TABLE *path_obj;
	ATOM_OBJECT_HEADER *obj_header;

	if (!amdgpu_atom_parse_data_header(ctx, index, &size, &frev, &crev, &data_offset))
		return false;

	if (crev < 2)
		return false;

	obj_header = (ATOM_OBJECT_HEADER *) (ctx->bios + data_offset);
	path_obj = (ATOM_DISPLAY_OBJECT_PATH_TABLE *)
	    (ctx->bios + data_offset +
	     le16_to_cpu(obj_header->usDisplayPathTableOffset));

	if (path_obj->ucNumOfDispPath)
		return true;
	else
		return false;
}