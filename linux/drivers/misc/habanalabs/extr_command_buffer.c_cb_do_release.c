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
struct hl_device {int /*<<< orphan*/  cb_pool_lock; int /*<<< orphan*/  cb_pool; } ;
struct hl_cb {int /*<<< orphan*/  pool_list; scalar_t__ is_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  cb_fini (struct hl_device*,struct hl_cb*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cb_do_release(struct hl_device *hdev, struct hl_cb *cb)
{
	if (cb->is_pool) {
		spin_lock(&hdev->cb_pool_lock);
		list_add(&cb->pool_list, &hdev->cb_pool);
		spin_unlock(&hdev->cb_pool_lock);
	} else {
		cb_fini(hdev, cb);
	}
}