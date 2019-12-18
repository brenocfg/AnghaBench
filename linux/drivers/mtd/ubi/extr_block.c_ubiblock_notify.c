#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  vol_type; } ;
struct ubi_notification {TYPE_1__ vi; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_OK ; 
 int /*<<< orphan*/  UBI_STATIC_VOLUME ; 
#define  UBI_VOLUME_ADDED 131 
#define  UBI_VOLUME_REMOVED 130 
#define  UBI_VOLUME_RESIZED 129 
#define  UBI_VOLUME_UPDATED 128 
 int /*<<< orphan*/  ubiblock_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  ubiblock_resize (TYPE_1__*) ; 

__attribute__((used)) static int ubiblock_notify(struct notifier_block *nb,
			 unsigned long notification_type, void *ns_ptr)
{
	struct ubi_notification *nt = ns_ptr;

	switch (notification_type) {
	case UBI_VOLUME_ADDED:
		/*
		 * We want to enforce explicit block device creation for
		 * volumes, so when a volume is added we do nothing.
		 */
		break;
	case UBI_VOLUME_REMOVED:
		ubiblock_remove(&nt->vi);
		break;
	case UBI_VOLUME_RESIZED:
		ubiblock_resize(&nt->vi);
		break;
	case UBI_VOLUME_UPDATED:
		/*
		 * If the volume is static, a content update might mean the
		 * size (i.e. used_bytes) was also changed.
		 */
		if (nt->vi.vol_type == UBI_STATIC_VOLUME)
			ubiblock_resize(&nt->vi);
		break;
	default:
		break;
	}
	return NOTIFY_OK;
}