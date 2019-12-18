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
typedef  size_t u8 ;
struct cam_ctl_t {int /*<<< orphan*/  lock; } ;
struct dvobj_priv {int /*<<< orphan*/ * cam_cache; struct cam_ctl_t cam_ctl; } ;
struct cam_entry_cache {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void clear_cam_cache(struct adapter *adapter, u8 id)
{
	struct dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	struct cam_ctl_t *cam_ctl = &dvobj->cam_ctl;

	spin_lock_bh(&cam_ctl->lock);

	memset(&(dvobj->cam_cache[id]), 0, sizeof(struct cam_entry_cache));

	spin_unlock_bh(&cam_ctl->lock);
}