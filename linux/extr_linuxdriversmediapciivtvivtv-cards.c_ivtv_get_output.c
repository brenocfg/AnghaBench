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
typedef  int u16 ;
struct v4l2_output {int index; int audioset; int /*<<< orphan*/  std; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct ivtv_card_output {int /*<<< orphan*/  name; } ;
struct ivtv {TYPE_1__* card; } ;
struct TYPE_2__ {int nof_outputs; struct ivtv_card_output* video_outputs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_OUTPUT_TYPE_ANALOG ; 
 int /*<<< orphan*/  V4L2_STD_ALL ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ivtv_get_output(struct ivtv *itv, u16 index, struct v4l2_output *output)
{
	const struct ivtv_card_output *card_output = itv->card->video_outputs + index;

	if (index >= itv->card->nof_outputs)
		return -EINVAL;
	output->index = index;
	strlcpy(output->name, card_output->name, sizeof(output->name));
	output->type = V4L2_OUTPUT_TYPE_ANALOG;
	output->audioset = 1;
	output->std = V4L2_STD_ALL;
	return 0;
}