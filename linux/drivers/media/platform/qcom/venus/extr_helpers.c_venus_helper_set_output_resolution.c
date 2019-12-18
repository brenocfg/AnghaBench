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
typedef  int /*<<< orphan*/  u32 ;
struct venus_inst {int dummy; } ;
struct hfi_framesize {unsigned int width; unsigned int height; int /*<<< orphan*/  buffer_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_PROPERTY_PARAM_FRAME_SIZE ; 
 int hfi_session_set_property (struct venus_inst*,int /*<<< orphan*/ ,struct hfi_framesize*) ; 

int venus_helper_set_output_resolution(struct venus_inst *inst,
				       unsigned int width, unsigned int height,
				       u32 buftype)
{
	u32 ptype = HFI_PROPERTY_PARAM_FRAME_SIZE;
	struct hfi_framesize fs;

	fs.buffer_type = buftype;
	fs.width = width;
	fs.height = height;

	return hfi_session_set_property(inst, ptype, &fs);
}