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
struct ubi_notification {int /*<<< orphan*/  vi; int /*<<< orphan*/  di; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_OK ; 
#define  UBI_VOLUME_ADDED 131 
#define  UBI_VOLUME_REMOVED 130 
#define  UBI_VOLUME_RESIZED 129 
#define  UBI_VOLUME_UPDATED 128 
 int /*<<< orphan*/  gluebi_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gluebi_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gluebi_resized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gluebi_updated (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gluebi_notify(struct notifier_block *nb, unsigned long l,
			 void *ns_ptr)
{
	struct ubi_notification *nt = ns_ptr;

	switch (l) {
	case UBI_VOLUME_ADDED:
		gluebi_create(&nt->di, &nt->vi);
		break;
	case UBI_VOLUME_REMOVED:
		gluebi_remove(&nt->vi);
		break;
	case UBI_VOLUME_RESIZED:
		gluebi_resized(&nt->vi);
		break;
	case UBI_VOLUME_UPDATED:
		gluebi_updated(&nt->vi);
		break;
	default:
		break;
	}
	return NOTIFY_OK;
}