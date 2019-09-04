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
typedef  int u32 ;
struct v4l2_ctrl_ops {int dummy; } ;
struct v4l2_ctrl_handler {int error; } ;
struct v4l2_ctrl {int /*<<< orphan*/  flags; } ;
struct lm3560_flash {TYPE_2__* subdev_led; TYPE_1__* pdata; int /*<<< orphan*/  led_mode; struct v4l2_ctrl_handler* ctrls_led; } ;
typedef  enum lm3560_led_id { ____Placeholder_lm3560_led_id } lm3560_led_id ;
struct TYPE_4__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct TYPE_3__ {int* max_flash_brt; int* max_torch_brt; int max_flash_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM3560_FLASH_BRT_MIN ; 
 int /*<<< orphan*/  LM3560_FLASH_BRT_STEP ; 
 int /*<<< orphan*/  LM3560_FLASH_TOUT_MIN ; 
 int /*<<< orphan*/  LM3560_FLASH_TOUT_STEP ; 
 int /*<<< orphan*/  LM3560_TORCH_BRT_MIN ; 
 int /*<<< orphan*/  LM3560_TORCH_BRT_STEP ; 
 int /*<<< orphan*/  V4L2_CID_FLASH_FAULT ; 
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
 int V4L2_FLASH_FAULT_TIMEOUT ; 
 int /*<<< orphan*/  V4L2_FLASH_LED_MODE_NONE ; 
 int V4L2_FLASH_LED_MODE_TORCH ; 
 int /*<<< orphan*/  V4L2_FLASH_STROBE_SOURCE_SOFTWARE ; 
 struct v4l2_ctrl_ops* lm3560_led_ctrl_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 struct v4l2_ctrl* v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,struct v4l2_ctrl_ops const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu (struct v4l2_ctrl_handler*,struct v4l2_ctrl_ops const*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm3560_init_controls(struct lm3560_flash *flash,
				enum lm3560_led_id led_no)
{
	struct v4l2_ctrl *fault;
	u32 max_flash_brt = flash->pdata->max_flash_brt[led_no];
	u32 max_torch_brt = flash->pdata->max_torch_brt[led_no];
	struct v4l2_ctrl_handler *hdl = &flash->ctrls_led[led_no];
	const struct v4l2_ctrl_ops *ops = &lm3560_led_ctrl_ops[led_no];

	v4l2_ctrl_handler_init(hdl, 8);

	/* flash mode */
	v4l2_ctrl_new_std_menu(hdl, ops, V4L2_CID_FLASH_LED_MODE,
			       V4L2_FLASH_LED_MODE_TORCH, ~0x7,
			       V4L2_FLASH_LED_MODE_NONE);
	flash->led_mode = V4L2_FLASH_LED_MODE_NONE;

	/* flash source */
	v4l2_ctrl_new_std_menu(hdl, ops, V4L2_CID_FLASH_STROBE_SOURCE,
			       0x1, ~0x3, V4L2_FLASH_STROBE_SOURCE_SOFTWARE);

	/* flash strobe */
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FLASH_STROBE, 0, 0, 0, 0);

	/* flash strobe stop */
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FLASH_STROBE_STOP, 0, 0, 0, 0);

	/* flash strobe timeout */
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FLASH_TIMEOUT,
			  LM3560_FLASH_TOUT_MIN,
			  flash->pdata->max_flash_timeout,
			  LM3560_FLASH_TOUT_STEP,
			  flash->pdata->max_flash_timeout);

	/* flash brt */
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FLASH_INTENSITY,
			  LM3560_FLASH_BRT_MIN, max_flash_brt,
			  LM3560_FLASH_BRT_STEP, max_flash_brt);

	/* torch brt */
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FLASH_TORCH_INTENSITY,
			  LM3560_TORCH_BRT_MIN, max_torch_brt,
			  LM3560_TORCH_BRT_STEP, max_torch_brt);

	/* fault */
	fault = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FLASH_FAULT, 0,
				  V4L2_FLASH_FAULT_OVER_VOLTAGE
				  | V4L2_FLASH_FAULT_OVER_TEMPERATURE
				  | V4L2_FLASH_FAULT_SHORT_CIRCUIT
				  | V4L2_FLASH_FAULT_TIMEOUT, 0, 0);
	if (fault != NULL)
		fault->flags |= V4L2_CTRL_FLAG_VOLATILE;

	if (hdl->error)
		return hdl->error;

	flash->subdev_led[led_no].ctrl_handler = hdl;
	return 0;
}