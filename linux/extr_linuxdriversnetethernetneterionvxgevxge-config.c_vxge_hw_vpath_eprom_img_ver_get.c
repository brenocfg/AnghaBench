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
typedef  scalar_t__ u64 ;
struct eprom_image {int /*<<< orphan*/  version; int /*<<< orphan*/  type; int /*<<< orphan*/  index; int /*<<< orphan*/  is_valid; } ;
struct __vxge_hw_virtualpath {int dummy; } ;
struct __vxge_hw_device {size_t first_vp_id; struct __vxge_hw_virtualpath* virtual_paths; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;

/* Variables and functions */
 int /*<<< orphan*/  VXGE_HW_FW_API_GET_EPROM_REV ; 
 int /*<<< orphan*/  VXGE_HW_GET_EPROM_IMAGE_INDEX (scalar_t__) ; 
 int /*<<< orphan*/  VXGE_HW_GET_EPROM_IMAGE_REV (scalar_t__) ; 
 int /*<<< orphan*/  VXGE_HW_GET_EPROM_IMAGE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  VXGE_HW_GET_EPROM_IMAGE_VALID (scalar_t__) ; 
 int VXGE_HW_MAX_ROM_IMAGES ; 
 int VXGE_HW_OK ; 
 int /*<<< orphan*/  VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_FW_MEMO ; 
 scalar_t__ VXGE_HW_RTS_ACCESS_STEER_ROM_IMAGE_INDEX (int) ; 
 int vxge_hw_vpath_fw_api (struct __vxge_hw_virtualpath*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*) ; 

enum vxge_hw_status
vxge_hw_vpath_eprom_img_ver_get(struct __vxge_hw_device *hldev,
				struct eprom_image *img)
{
	u64 data0 = 0, data1 = 0, steer_ctrl = 0;
	struct __vxge_hw_virtualpath *vpath;
	enum vxge_hw_status status;
	int i;

	vpath = &hldev->virtual_paths[hldev->first_vp_id];

	for (i = 0; i < VXGE_HW_MAX_ROM_IMAGES; i++) {
		data0 = VXGE_HW_RTS_ACCESS_STEER_ROM_IMAGE_INDEX(i);
		data1 = steer_ctrl = 0;

		status = vxge_hw_vpath_fw_api(vpath,
			VXGE_HW_FW_API_GET_EPROM_REV,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_FW_MEMO,
			0, &data0, &data1, &steer_ctrl);
		if (status != VXGE_HW_OK)
			break;

		img[i].is_valid = VXGE_HW_GET_EPROM_IMAGE_VALID(data0);
		img[i].index = VXGE_HW_GET_EPROM_IMAGE_INDEX(data0);
		img[i].type = VXGE_HW_GET_EPROM_IMAGE_TYPE(data0);
		img[i].version = VXGE_HW_GET_EPROM_IMAGE_REV(data0);
	}

	return status;
}