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
typedef  int /*<<< orphan*/  u32 ;
struct hl_device {int /*<<< orphan*/  dev; } ;
struct hl_cb_mgr {int /*<<< orphan*/  cb_lock; int /*<<< orphan*/  cb_handles; } ;
struct hl_cb {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct hl_cb* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct hl_cb *hl_cb_get(struct hl_device *hdev, struct hl_cb_mgr *mgr,
			u32 handle)
{
	struct hl_cb *cb;

	spin_lock(&mgr->cb_lock);
	cb = idr_find(&mgr->cb_handles, handle);

	if (!cb) {
		spin_unlock(&mgr->cb_lock);
		dev_warn(hdev->dev,
			"CB get failed, no match to handle %d\n", handle);
		return NULL;
	}

	kref_get(&cb->refcount);

	spin_unlock(&mgr->cb_lock);

	return cb;

}