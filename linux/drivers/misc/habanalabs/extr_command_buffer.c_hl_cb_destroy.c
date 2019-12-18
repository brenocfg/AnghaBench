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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct hl_device {int /*<<< orphan*/  dev; } ;
struct hl_cb_mgr {int /*<<< orphan*/  cb_lock; int /*<<< orphan*/  cb_handles; } ;
struct hl_cb {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  cb_release ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 struct hl_cb* idr_find (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int hl_cb_destroy(struct hl_device *hdev, struct hl_cb_mgr *mgr, u64 cb_handle)
{
	struct hl_cb *cb;
	u32 handle;
	int rc = 0;

	/*
	 * handle was given to user to do mmap, I need to shift it back to
	 * how the idr module gave it to me
	 */
	cb_handle >>= PAGE_SHIFT;
	handle = (u32) cb_handle;

	spin_lock(&mgr->cb_lock);

	cb = idr_find(&mgr->cb_handles, handle);
	if (cb) {
		idr_remove(&mgr->cb_handles, handle);
		spin_unlock(&mgr->cb_lock);
		kref_put(&cb->refcount, cb_release);
	} else {
		spin_unlock(&mgr->cb_lock);
		dev_err(hdev->dev,
			"CB destroy failed, no match to handle 0x%x\n", handle);
		rc = -EINVAL;
	}

	return rc;
}