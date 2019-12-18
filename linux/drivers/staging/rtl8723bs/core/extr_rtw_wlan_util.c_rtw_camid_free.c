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
typedef  scalar_t__ u8 ;
struct cam_ctl_t {int /*<<< orphan*/  lock; int /*<<< orphan*/  bitmap; } ;
struct dvobj_priv {struct cam_ctl_t cam_ctl; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 scalar_t__ TOTAL_CAM_ENTRY ; 
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void rtw_camid_free(struct adapter *adapter, u8 cam_id)
{
	struct dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	struct cam_ctl_t *cam_ctl = &dvobj->cam_ctl;

	spin_lock_bh(&cam_ctl->lock);

	if (cam_id < TOTAL_CAM_ENTRY)
		cam_ctl->bitmap &= ~(BIT(cam_id));

	spin_unlock_bh(&cam_ctl->lock);
}