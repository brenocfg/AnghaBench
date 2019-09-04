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
struct TYPE_2__ {int /*<<< orphan*/  fwnode; } ;
struct v4l2_async_subdev {int match_type; TYPE_1__ match; } ;
struct v4l2_async_notifier {unsigned int num_subdevs; struct v4l2_async_subdev** subdevs; scalar_t__ max_subdevs; } ;

/* Variables and functions */
#define  V4L2_ASYNC_MATCH_FWNODE 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  fwnode_handle_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct v4l2_async_subdev*) ; 
 int /*<<< orphan*/  kvfree (struct v4l2_async_subdev**) ; 

void v4l2_async_notifier_cleanup(struct v4l2_async_notifier *notifier)
{
	unsigned int i;

	if (!notifier || !notifier->max_subdevs)
		return;

	for (i = 0; i < notifier->num_subdevs; i++) {
		struct v4l2_async_subdev *asd = notifier->subdevs[i];

		switch (asd->match_type) {
		case V4L2_ASYNC_MATCH_FWNODE:
			fwnode_handle_put(asd->match.fwnode);
			break;
		default:
			WARN_ON_ONCE(true);
			break;
		}

		kfree(asd);
	}

	notifier->max_subdevs = 0;
	notifier->num_subdevs = 0;

	kvfree(notifier->subdevs);
	notifier->subdevs = NULL;
}