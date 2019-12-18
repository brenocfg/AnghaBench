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
struct uvc_processing_unit_descriptor {int bUnitID; int bSourceID; int bControlSize; int* bmControls; scalar_t__ iProcessing; void* wMaxMultiplier; int /*<<< orphan*/  bDescriptorSubType; void* bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct uvc_output_terminal_descriptor {int bTerminalID; int bSourceID; scalar_t__ iTerminal; scalar_t__ bAssocTerminal; void* wTerminalType; int /*<<< orphan*/  bDescriptorSubType; void* bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct uvc_descriptor_header {int dummy; } ;
struct uvc_color_matching_descriptor {int bColorPrimaries; int bTransferCharacteristics; int bMatrixCoefficients; int /*<<< orphan*/  bDescriptorSubType; void* bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct uvc_camera_terminal_descriptor {int bTerminalID; int bControlSize; int* bmControls; void* wOcularFocalLength; void* wObjectiveFocalLengthMax; void* wObjectiveFocalLengthMin; scalar_t__ iTerminal; scalar_t__ bAssocTerminal; void* wTerminalType; int /*<<< orphan*/  bDescriptorSubType; void* bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct usb_function_instance {int /*<<< orphan*/  free_func_inst; } ;
struct f_uvc_opts {int streaming_interval; int streaming_maxpacket; struct usb_function_instance func_inst; struct uvc_descriptor_header const* const* ss_control; struct uvc_descriptor_header** uvc_ss_control_cls; struct uvc_descriptor_header const* const* fs_control; struct uvc_descriptor_header** uvc_fs_control_cls; struct uvc_color_matching_descriptor uvc_color_matching; struct uvc_output_terminal_descriptor uvc_output_terminal; struct uvc_processing_unit_descriptor uvc_processing; struct uvc_camera_terminal_descriptor uvc_camera_terminal; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct usb_function_instance* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* USB_DT_CS_INTERFACE ; 
 int /*<<< orphan*/  UVC_DT_CAMERA_TERMINAL_SIZE (int) ; 
 int /*<<< orphan*/  UVC_DT_COLOR_MATCHING_SIZE ; 
 int /*<<< orphan*/  UVC_DT_OUTPUT_TERMINAL_SIZE ; 
 int /*<<< orphan*/  UVC_DT_PROCESSING_UNIT_SIZE (int) ; 
 int /*<<< orphan*/  UVC_VC_INPUT_TERMINAL ; 
 int /*<<< orphan*/  UVC_VC_OUTPUT_TERMINAL ; 
 int /*<<< orphan*/  UVC_VC_PROCESSING_UNIT ; 
 int /*<<< orphan*/  UVC_VS_COLORFORMAT ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (struct f_uvc_opts*) ; 
 struct f_uvc_opts* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvc_free_inst ; 
 int uvcg_attach_configfs (struct f_uvc_opts*) ; 

__attribute__((used)) static struct usb_function_instance *uvc_alloc_inst(void)
{
	struct f_uvc_opts *opts;
	struct uvc_camera_terminal_descriptor *cd;
	struct uvc_processing_unit_descriptor *pd;
	struct uvc_output_terminal_descriptor *od;
	struct uvc_color_matching_descriptor *md;
	struct uvc_descriptor_header **ctl_cls;
	int ret;

	opts = kzalloc(sizeof(*opts), GFP_KERNEL);
	if (!opts)
		return ERR_PTR(-ENOMEM);
	opts->func_inst.free_func_inst = uvc_free_inst;
	mutex_init(&opts->lock);

	cd = &opts->uvc_camera_terminal;
	cd->bLength			= UVC_DT_CAMERA_TERMINAL_SIZE(3);
	cd->bDescriptorType		= USB_DT_CS_INTERFACE;
	cd->bDescriptorSubType		= UVC_VC_INPUT_TERMINAL;
	cd->bTerminalID			= 1;
	cd->wTerminalType		= cpu_to_le16(0x0201);
	cd->bAssocTerminal		= 0;
	cd->iTerminal			= 0;
	cd->wObjectiveFocalLengthMin	= cpu_to_le16(0);
	cd->wObjectiveFocalLengthMax	= cpu_to_le16(0);
	cd->wOcularFocalLength		= cpu_to_le16(0);
	cd->bControlSize		= 3;
	cd->bmControls[0]		= 2;
	cd->bmControls[1]		= 0;
	cd->bmControls[2]		= 0;

	pd = &opts->uvc_processing;
	pd->bLength			= UVC_DT_PROCESSING_UNIT_SIZE(2);
	pd->bDescriptorType		= USB_DT_CS_INTERFACE;
	pd->bDescriptorSubType		= UVC_VC_PROCESSING_UNIT;
	pd->bUnitID			= 2;
	pd->bSourceID			= 1;
	pd->wMaxMultiplier		= cpu_to_le16(16*1024);
	pd->bControlSize		= 2;
	pd->bmControls[0]		= 1;
	pd->bmControls[1]		= 0;
	pd->iProcessing			= 0;

	od = &opts->uvc_output_terminal;
	od->bLength			= UVC_DT_OUTPUT_TERMINAL_SIZE;
	od->bDescriptorType		= USB_DT_CS_INTERFACE;
	od->bDescriptorSubType		= UVC_VC_OUTPUT_TERMINAL;
	od->bTerminalID			= 3;
	od->wTerminalType		= cpu_to_le16(0x0101);
	od->bAssocTerminal		= 0;
	od->bSourceID			= 2;
	od->iTerminal			= 0;

	md = &opts->uvc_color_matching;
	md->bLength			= UVC_DT_COLOR_MATCHING_SIZE;
	md->bDescriptorType		= USB_DT_CS_INTERFACE;
	md->bDescriptorSubType		= UVC_VS_COLORFORMAT;
	md->bColorPrimaries		= 1;
	md->bTransferCharacteristics	= 1;
	md->bMatrixCoefficients		= 4;

	/* Prepare fs control class descriptors for configfs-based gadgets */
	ctl_cls = opts->uvc_fs_control_cls;
	ctl_cls[0] = NULL;	/* assigned elsewhere by configfs */
	ctl_cls[1] = (struct uvc_descriptor_header *)cd;
	ctl_cls[2] = (struct uvc_descriptor_header *)pd;
	ctl_cls[3] = (struct uvc_descriptor_header *)od;
	ctl_cls[4] = NULL;	/* NULL-terminate */
	opts->fs_control =
		(const struct uvc_descriptor_header * const *)ctl_cls;

	/* Prepare hs control class descriptors for configfs-based gadgets */
	ctl_cls = opts->uvc_ss_control_cls;
	ctl_cls[0] = NULL;	/* assigned elsewhere by configfs */
	ctl_cls[1] = (struct uvc_descriptor_header *)cd;
	ctl_cls[2] = (struct uvc_descriptor_header *)pd;
	ctl_cls[3] = (struct uvc_descriptor_header *)od;
	ctl_cls[4] = NULL;	/* NULL-terminate */
	opts->ss_control =
		(const struct uvc_descriptor_header * const *)ctl_cls;

	opts->streaming_interval = 1;
	opts->streaming_maxpacket = 1024;

	ret = uvcg_attach_configfs(opts);
	if (ret < 0) {
		kfree(opts);
		return ERR_PTR(ret);
	}

	return &opts->func_inst;
}