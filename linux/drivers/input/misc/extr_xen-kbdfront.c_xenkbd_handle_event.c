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
union xenkbd_in_event {int type; int /*<<< orphan*/  mtouch; int /*<<< orphan*/  pos; int /*<<< orphan*/  key; int /*<<< orphan*/  motion; } ;
struct xenkbd_info {int dummy; } ;

/* Variables and functions */
#define  XENKBD_TYPE_KEY 131 
#define  XENKBD_TYPE_MOTION 130 
#define  XENKBD_TYPE_MTOUCH 129 
#define  XENKBD_TYPE_POS 128 
 int /*<<< orphan*/  xenkbd_handle_key_event (struct xenkbd_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenkbd_handle_motion_event (struct xenkbd_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenkbd_handle_mt_event (struct xenkbd_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenkbd_handle_position_event (struct xenkbd_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xenkbd_handle_event(struct xenkbd_info *info,
				union xenkbd_in_event *event)
{
	switch (event->type) {
	case XENKBD_TYPE_MOTION:
		xenkbd_handle_motion_event(info, &event->motion);
		break;

	case XENKBD_TYPE_KEY:
		xenkbd_handle_key_event(info, &event->key);
		break;

	case XENKBD_TYPE_POS:
		xenkbd_handle_position_event(info, &event->pos);
		break;

	case XENKBD_TYPE_MTOUCH:
		xenkbd_handle_mt_event(info, &event->mtouch);
		break;
	}
}