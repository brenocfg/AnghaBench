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
struct cam_entry_cache {int /*<<< orphan*/  key; int /*<<< orphan*/  mac; int /*<<< orphan*/  ctrl; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _write_cam (struct adapter*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 
 int /*<<< orphan*/  memcpy (struct cam_entry_cache*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

inline void write_cam_from_cache(struct adapter *adapter, u8 id)
{
	struct dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	struct cam_ctl_t *cam_ctl = &dvobj->cam_ctl;
	struct cam_entry_cache cache;

	spin_lock_bh(&cam_ctl->lock);
	memcpy(&cache, &dvobj->cam_cache[id], sizeof(struct cam_entry_cache));
	spin_unlock_bh(&cam_ctl->lock);

	_write_cam(adapter, id, cache.ctrl, cache.mac, cache.key);
}