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
typedef  scalar_t__ u16 ;
struct v4l2_audioout {int /*<<< orphan*/  name; } ;
struct ivtv {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/ * video_outputs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memset (struct v4l2_audioout*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

int ivtv_get_audio_output(struct ivtv *itv, u16 index, struct v4l2_audioout *aud_output)
{
	memset(aud_output, 0, sizeof(*aud_output));
	if (itv->card->video_outputs == NULL || index != 0)
		return -EINVAL;
	strscpy(aud_output->name, "A/V Audio Out", sizeof(aud_output->name));
	return 0;
}