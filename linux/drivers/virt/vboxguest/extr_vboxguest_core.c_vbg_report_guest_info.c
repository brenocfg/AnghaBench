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
struct vmmdev_guest_info2 {int /*<<< orphan*/  name; int /*<<< orphan*/  additions_features; int /*<<< orphan*/  additions_revision; int /*<<< orphan*/  additions_build; int /*<<< orphan*/  additions_minor; int /*<<< orphan*/  additions_major; int /*<<< orphan*/  os_type; int /*<<< orphan*/  interface_version; } ;
struct vmmdev_guest_info {int /*<<< orphan*/  name; int /*<<< orphan*/  additions_features; int /*<<< orphan*/  additions_revision; int /*<<< orphan*/  additions_build; int /*<<< orphan*/  additions_minor; int /*<<< orphan*/  additions_major; int /*<<< orphan*/  os_type; int /*<<< orphan*/  interface_version; } ;
struct vbg_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  VBG_KERNEL_REQUEST ; 
 int /*<<< orphan*/  VBG_SVN_REV ; 
 int /*<<< orphan*/  VBG_VERSION_BUILD ; 
 int /*<<< orphan*/  VBG_VERSION_MAJOR ; 
 int /*<<< orphan*/  VBG_VERSION_MINOR ; 
 int /*<<< orphan*/  VBG_VERSION_STRING ; 
 int VERR_NOT_IMPLEMENTED ; 
 int VERR_NOT_SUPPORTED ; 
 int VINF_SUCCESS ; 
 int /*<<< orphan*/  VMMDEVREQ_REPORT_GUEST_INFO ; 
 int /*<<< orphan*/  VMMDEVREQ_REPORT_GUEST_INFO2 ; 
 int /*<<< orphan*/  VMMDEV_GUEST_INFO2_ADDITIONS_FEATURES_REQUESTOR_INFO ; 
 int /*<<< orphan*/  VMMDEV_OSTYPE_LINUX26 ; 
 int /*<<< orphan*/  VMMDEV_OSTYPE_X64 ; 
 int /*<<< orphan*/  VMMDEV_VERSION ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct vmmdev_guest_info2* vbg_req_alloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbg_req_free (struct vmmdev_guest_info2*,int) ; 
 int vbg_req_perform (struct vbg_dev*,struct vmmdev_guest_info2*) ; 
 int vbg_status_code_to_errno (int) ; 

__attribute__((used)) static int vbg_report_guest_info(struct vbg_dev *gdev)
{
	/*
	 * Allocate and fill in the two guest info reports.
	 */
	struct vmmdev_guest_info *req1 = NULL;
	struct vmmdev_guest_info2 *req2 = NULL;
	int rc, ret = -ENOMEM;

	req1 = vbg_req_alloc(sizeof(*req1), VMMDEVREQ_REPORT_GUEST_INFO,
			     VBG_KERNEL_REQUEST);
	req2 = vbg_req_alloc(sizeof(*req2), VMMDEVREQ_REPORT_GUEST_INFO2,
			     VBG_KERNEL_REQUEST);
	if (!req1 || !req2)
		goto out_free;

	req1->interface_version = VMMDEV_VERSION;
	req1->os_type = VMMDEV_OSTYPE_LINUX26;
#if __BITS_PER_LONG == 64
	req1->os_type |= VMMDEV_OSTYPE_X64;
#endif

	req2->additions_major = VBG_VERSION_MAJOR;
	req2->additions_minor = VBG_VERSION_MINOR;
	req2->additions_build = VBG_VERSION_BUILD;
	req2->additions_revision = VBG_SVN_REV;
	req2->additions_features =
		VMMDEV_GUEST_INFO2_ADDITIONS_FEATURES_REQUESTOR_INFO;
	strlcpy(req2->name, VBG_VERSION_STRING,
		sizeof(req2->name));

	/*
	 * There are two protocols here:
	 *      1. INFO2 + INFO1. Supported by >=3.2.51.
	 *      2. INFO1 and optionally INFO2. The old protocol.
	 *
	 * We try protocol 2 first.  It will fail with VERR_NOT_SUPPORTED
	 * if not supported by the VMMDev (message ordering requirement).
	 */
	rc = vbg_req_perform(gdev, req2);
	if (rc >= 0) {
		rc = vbg_req_perform(gdev, req1);
	} else if (rc == VERR_NOT_SUPPORTED || rc == VERR_NOT_IMPLEMENTED) {
		rc = vbg_req_perform(gdev, req1);
		if (rc >= 0) {
			rc = vbg_req_perform(gdev, req2);
			if (rc == VERR_NOT_IMPLEMENTED)
				rc = VINF_SUCCESS;
		}
	}
	ret = vbg_status_code_to_errno(rc);

out_free:
	vbg_req_free(req2, sizeof(*req2));
	vbg_req_free(req1, sizeof(*req1));
	return ret;
}