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
struct dpu_crtc_respool {int /*<<< orphan*/  rp_lock; int /*<<< orphan*/  rp_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dpu_crtc_rp_reclaim (struct dpu_crtc_respool*,int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _dpu_crtc_rp_destroy(struct dpu_crtc_respool *rp)
{
	mutex_lock(rp->rp_lock);
	list_del_init(&rp->rp_list);
	_dpu_crtc_rp_reclaim(rp, true);
	mutex_unlock(rp->rp_lock);
}