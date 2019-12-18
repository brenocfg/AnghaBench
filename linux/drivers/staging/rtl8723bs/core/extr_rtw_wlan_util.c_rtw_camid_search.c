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
typedef  int /*<<< orphan*/  u8 ;
struct cam_ctl_t {int /*<<< orphan*/  lock; } ;
struct dvobj_priv {struct cam_ctl_t cam_ctl; } ;
struct adapter {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
 int _rtw_camid_search (struct adapter*,int /*<<< orphan*/ *,int) ; 
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

s16 rtw_camid_search(struct adapter *adapter, u8 *addr, s16 kid)
{
	struct dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	struct cam_ctl_t *cam_ctl = &dvobj->cam_ctl;
	s16 cam_id = -1;

	spin_lock_bh(&cam_ctl->lock);
	cam_id = _rtw_camid_search(adapter, addr, kid);
	spin_unlock_bh(&cam_ctl->lock);

	return cam_id;
}