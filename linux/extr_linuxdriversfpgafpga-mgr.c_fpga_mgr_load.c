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
struct fpga_manager {int dummy; } ;
struct fpga_image_info {scalar_t__ firmware_name; scalar_t__ count; scalar_t__ buf; scalar_t__ sgt; } ;

/* Variables and functions */
 int EINVAL ; 
 int fpga_mgr_buf_load (struct fpga_manager*,struct fpga_image_info*,scalar_t__,scalar_t__) ; 
 int fpga_mgr_buf_load_sg (struct fpga_manager*,struct fpga_image_info*,scalar_t__) ; 
 int fpga_mgr_firmware_load (struct fpga_manager*,struct fpga_image_info*,scalar_t__) ; 

int fpga_mgr_load(struct fpga_manager *mgr, struct fpga_image_info *info)
{
	if (info->sgt)
		return fpga_mgr_buf_load_sg(mgr, info, info->sgt);
	if (info->buf && info->count)
		return fpga_mgr_buf_load(mgr, info, info->buf, info->count);
	if (info->firmware_name)
		return fpga_mgr_firmware_load(mgr, info, info->firmware_name);
	return -EINVAL;
}