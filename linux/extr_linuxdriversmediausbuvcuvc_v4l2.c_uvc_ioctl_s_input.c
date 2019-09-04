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
typedef  unsigned int u32 ;
struct uvc_video_chain {TYPE_2__* dev; TYPE_1__* selector; } ;
struct uvc_fh {struct uvc_video_chain* chain; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int quirks; int /*<<< orphan*/  intfnum; } ;
struct TYPE_3__ {unsigned int bNrInPins; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int UVC_QUIRK_IGNORE_SELECTOR_UNIT ; 
 int /*<<< orphan*/  UVC_SET_CUR ; 
 int /*<<< orphan*/  UVC_SU_INPUT_SELECT_CONTROL ; 
 int uvc_acquire_privileges (struct uvc_fh*) ; 
 int uvc_query_ctrl (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int) ; 

__attribute__((used)) static int uvc_ioctl_s_input(struct file *file, void *fh, unsigned int input)
{
	struct uvc_fh *handle = fh;
	struct uvc_video_chain *chain = handle->chain;
	int ret;
	u32 i;

	ret = uvc_acquire_privileges(handle);
	if (ret < 0)
		return ret;

	if (chain->selector == NULL ||
	    (chain->dev->quirks & UVC_QUIRK_IGNORE_SELECTOR_UNIT)) {
		if (input)
			return -EINVAL;
		return 0;
	}

	if (input >= chain->selector->bNrInPins)
		return -EINVAL;

	i = input + 1;
	return uvc_query_ctrl(chain->dev, UVC_SET_CUR, chain->selector->id,
			      chain->dev->intfnum, UVC_SU_INPUT_SELECT_CONTROL,
			      &i, 1);
}