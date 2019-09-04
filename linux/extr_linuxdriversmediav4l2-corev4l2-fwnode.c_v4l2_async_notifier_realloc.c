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
struct v4l2_async_subdev {int dummy; } ;
struct v4l2_async_notifier {unsigned int max_subdevs; int num_subdevs; struct v4l2_async_subdev** subdevs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  kvfree (struct v4l2_async_subdev**) ; 
 struct v4l2_async_subdev** kvmalloc_array (unsigned int,int,int) ; 
 int /*<<< orphan*/  memcpy (struct v4l2_async_subdev**,struct v4l2_async_subdev**,int) ; 

__attribute__((used)) static int v4l2_async_notifier_realloc(struct v4l2_async_notifier *notifier,
				       unsigned int max_subdevs)
{
	struct v4l2_async_subdev **subdevs;

	if (max_subdevs <= notifier->max_subdevs)
		return 0;

	subdevs = kvmalloc_array(
		max_subdevs, sizeof(*notifier->subdevs),
		GFP_KERNEL | __GFP_ZERO);
	if (!subdevs)
		return -ENOMEM;

	if (notifier->subdevs) {
		memcpy(subdevs, notifier->subdevs,
		       sizeof(*subdevs) * notifier->num_subdevs);

		kvfree(notifier->subdevs);
	}

	notifier->subdevs = subdevs;
	notifier->max_subdevs = max_subdevs;

	return 0;
}