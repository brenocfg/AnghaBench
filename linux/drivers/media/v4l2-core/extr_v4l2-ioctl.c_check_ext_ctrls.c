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
struct v4l2_ext_controls {size_t count; scalar_t__ which; size_t error_idx; TYPE_1__* controls; scalar_t__* reserved; } ;
typedef  size_t __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  id; scalar_t__* reserved2; } ;

/* Variables and functions */
 scalar_t__ V4L2_CID_PRIVATE_BASE ; 
 scalar_t__ V4L2_CTRL_ID2WHICH (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_ext_ctrls(struct v4l2_ext_controls *c, int allow_priv)
{
	__u32 i;

	/* zero the reserved fields */
	c->reserved[0] = 0;
	for (i = 0; i < c->count; i++)
		c->controls[i].reserved2[0] = 0;

	/* V4L2_CID_PRIVATE_BASE cannot be used as control class
	   when using extended controls.
	   Only when passed in through VIDIOC_G_CTRL and VIDIOC_S_CTRL
	   is it allowed for backwards compatibility.
	 */
	if (!allow_priv && c->which == V4L2_CID_PRIVATE_BASE)
		return 0;
	if (!c->which)
		return 1;
	/* Check that all controls are from the same control class. */
	for (i = 0; i < c->count; i++) {
		if (V4L2_CTRL_ID2WHICH(c->controls[i].id) != c->which) {
			c->error_idx = i;
			return 0;
		}
	}
	return 1;
}