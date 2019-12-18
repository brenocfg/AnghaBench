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
struct vm_area_struct {struct gru_vma_data* vm_private_data; } ;
struct gru_vma_data {int /*<<< orphan*/  vd_lock; } ;
struct gru_thread_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gru_dbg (int /*<<< orphan*/ ,char*,struct vm_area_struct*,struct gru_thread_state*) ; 
 struct gru_thread_state* gru_find_current_gts_nolock (struct gru_vma_data*,int) ; 
 int /*<<< orphan*/  grudev ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct gru_thread_state *gru_find_thread_state(struct vm_area_struct *vma,
					int tsid)
{
	struct gru_vma_data *vdata = vma->vm_private_data;
	struct gru_thread_state *gts;

	spin_lock(&vdata->vd_lock);
	gts = gru_find_current_gts_nolock(vdata, tsid);
	spin_unlock(&vdata->vd_lock);
	gru_dbg(grudev, "vma %p, gts %p\n", vma, gts);
	return gts;
}