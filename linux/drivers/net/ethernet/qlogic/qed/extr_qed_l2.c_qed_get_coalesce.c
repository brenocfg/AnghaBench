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
typedef  int /*<<< orphan*/  u16 ;
struct qed_queue_cid {struct qed_hwfn* p_owner; } ;
struct qed_hwfn {int dummy; } ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QED_MSG_DEBUG ; 
 int qed_get_queue_coalesce (struct qed_hwfn*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int qed_get_coalesce(struct qed_dev *cdev, u16 *coal, void *handle)
{
	struct qed_queue_cid *p_cid = handle;
	struct qed_hwfn *p_hwfn;
	int rc;

	p_hwfn = p_cid->p_owner;
	rc = qed_get_queue_coalesce(p_hwfn, coal, handle);
	if (rc)
		DP_VERBOSE(cdev, QED_MSG_DEBUG,
			   "Unable to read queue coalescing\n");

	return rc;
}