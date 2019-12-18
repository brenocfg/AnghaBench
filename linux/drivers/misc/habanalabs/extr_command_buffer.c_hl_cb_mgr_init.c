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
struct hl_cb_mgr {int /*<<< orphan*/  cb_handles; int /*<<< orphan*/  cb_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void hl_cb_mgr_init(struct hl_cb_mgr *mgr)
{
	spin_lock_init(&mgr->cb_lock);
	idr_init(&mgr->cb_handles);
}