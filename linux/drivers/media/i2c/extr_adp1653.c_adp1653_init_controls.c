#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int error; } ;
struct TYPE_7__ {TYPE_3__* ctrl_handler; } ;
struct adp1653_flash {TYPE_3__ ctrls; TYPE_2__ subdev; TYPE_1__* platform_data; void* indicator_intensity; void* torch_intensity; void* flash_intensity; void* flash_timeout; int /*<<< orphan*/  led_mode; } ;
struct TYPE_6__ {int max_flash_timeout; int max_flash_intensity; int max_torch_intensity; int max_indicator_intensity; } ;

/* Variables and functions */
 int ADP1653_FLASH_INTENSITY_MIN ; 
 int ADP1653_FLASH_INTENSITY_STEP ; 
 int ADP1653_INDICATOR_INTENSITY_MIN ; 
 int ADP1653_INDICATOR_INTENSITY_STEP ; 
 int ADP1653_TORCH_INTENSITY_MIN ; 
 int TIMEOUT_MIN ; 
 int TIMEOUT_STEP ; 
 int /*<<< orphan*/  V4L2_CID_FLASH_FAULT ; 
 int /*<<< orphan*/  V4L2_CID_FLASH_INDICATOR_INTENSITY ; 
 int /*<<< orphan*/  V4L2_CID_FLASH_INTENSITY ; 
 int /*<<< orphan*/  V4L2_CID_FLASH_LED_MODE ; 
 int /*<<< orphan*/  V4L2_CID_FLASH_STROBE ; 
 int /*<<< orphan*/  V4L2_CID_FLASH_STROBE_SOURCE ; 
 int /*<<< orphan*/  V4L2_CID_FLASH_STROBE_STOP ; 
 int /*<<< orphan*/  V4L2_CID_FLASH_TIMEOUT ; 
 int /*<<< orphan*/  V4L2_CID_FLASH_TORCH_INTENSITY ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_VOLATILE ; 
 int V4L2_FLASH_FAULT_OVER_TEMPERATURE ; 
 int V4L2_FLASH_FAULT_OVER_VOLTAGE ; 
 int V4L2_FLASH_FAULT_SHORT_CIRCUIT ; 
 int /*<<< orphan*/  V4L2_FLASH_LED_MODE_TORCH ; 
 int /*<<< orphan*/  V4L2_FLASH_STROBE_SOURCE_SOFTWARE ; 
 int /*<<< orphan*/  adp1653_ctrl_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_3__*,int) ; 
 void* v4l2_ctrl_new_std (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adp1653_init_controls(struct adp1653_flash *flash)
{
	struct v4l2_ctrl *fault;

	v4l2_ctrl_handler_init(&flash->ctrls, 9);

	flash->led_mode =
		v4l2_ctrl_new_std_menu(&flash->ctrls, &adp1653_ctrl_ops,
				       V4L2_CID_FLASH_LED_MODE,
				       V4L2_FLASH_LED_MODE_TORCH, ~0x7, 0);
	v4l2_ctrl_new_std_menu(&flash->ctrls, &adp1653_ctrl_ops,
			       V4L2_CID_FLASH_STROBE_SOURCE,
			       V4L2_FLASH_STROBE_SOURCE_SOFTWARE, ~0x1, 0);
	v4l2_ctrl_new_std(&flash->ctrls, &adp1653_ctrl_ops,
			  V4L2_CID_FLASH_STROBE, 0, 0, 0, 0);
	v4l2_ctrl_new_std(&flash->ctrls, &adp1653_ctrl_ops,
			  V4L2_CID_FLASH_STROBE_STOP, 0, 0, 0, 0);
	flash->flash_timeout =
		v4l2_ctrl_new_std(&flash->ctrls, &adp1653_ctrl_ops,
				  V4L2_CID_FLASH_TIMEOUT, TIMEOUT_MIN,
				  flash->platform_data->max_flash_timeout,
				  TIMEOUT_STEP,
				  flash->platform_data->max_flash_timeout);
	flash->flash_intensity =
		v4l2_ctrl_new_std(&flash->ctrls, &adp1653_ctrl_ops,
				  V4L2_CID_FLASH_INTENSITY,
				  ADP1653_FLASH_INTENSITY_MIN,
				  flash->platform_data->max_flash_intensity,
				  1, flash->platform_data->max_flash_intensity);
	flash->torch_intensity =
		v4l2_ctrl_new_std(&flash->ctrls, &adp1653_ctrl_ops,
				  V4L2_CID_FLASH_TORCH_INTENSITY,
				  ADP1653_TORCH_INTENSITY_MIN,
				  flash->platform_data->max_torch_intensity,
				  ADP1653_FLASH_INTENSITY_STEP,
				  flash->platform_data->max_torch_intensity);
	flash->indicator_intensity =
		v4l2_ctrl_new_std(&flash->ctrls, &adp1653_ctrl_ops,
				  V4L2_CID_FLASH_INDICATOR_INTENSITY,
				  ADP1653_INDICATOR_INTENSITY_MIN,
				  flash->platform_data->max_indicator_intensity,
				  ADP1653_INDICATOR_INTENSITY_STEP,
				  ADP1653_INDICATOR_INTENSITY_MIN);
	fault = v4l2_ctrl_new_std(&flash->ctrls, &adp1653_ctrl_ops,
				  V4L2_CID_FLASH_FAULT, 0,
				  V4L2_FLASH_FAULT_OVER_VOLTAGE
				  | V4L2_FLASH_FAULT_OVER_TEMPERATURE
				  | V4L2_FLASH_FAULT_SHORT_CIRCUIT, 0, 0);

	if (flash->ctrls.error)
		return flash->ctrls.error;

	fault->flags |= V4L2_CTRL_FLAG_VOLATILE;

	flash->subdev.ctrl_handler = &flash->ctrls;
	return 0;
}