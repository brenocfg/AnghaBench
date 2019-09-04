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
struct v4l2_audioout {scalar_t__ index; } ;
struct ivtv {TYPE_1__* card; } ;
struct file {int dummy; } ;
struct TYPE_4__ {struct ivtv* itv; } ;
struct TYPE_3__ {int /*<<< orphan*/ * video_outputs; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__* fh2id (void*) ; 

__attribute__((used)) static int ivtv_s_audout(struct file *file, void *fh, const struct v4l2_audioout *vout)
{
	struct ivtv *itv = fh2id(fh)->itv;

	if (itv->card->video_outputs == NULL || vout->index != 0)
		return -EINVAL;
	return 0;
}