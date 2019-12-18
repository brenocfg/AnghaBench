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
struct uvc_video_chain {int /*<<< orphan*/  prio; struct uvc_device* dev; int /*<<< orphan*/  ctrl_mutex; int /*<<< orphan*/  entities; } ;
struct uvc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct uvc_video_chain* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_prio_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct uvc_video_chain *uvc_alloc_chain(struct uvc_device *dev)
{
	struct uvc_video_chain *chain;

	chain = kzalloc(sizeof(*chain), GFP_KERNEL);
	if (chain == NULL)
		return NULL;

	INIT_LIST_HEAD(&chain->entities);
	mutex_init(&chain->ctrl_mutex);
	chain->dev = dev;
	v4l2_prio_init(&chain->prio);

	return chain;
}