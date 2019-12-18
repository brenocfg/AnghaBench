#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct cam_ctl_t {int /*<<< orphan*/  lock; } ;
struct dvobj_priv {TYPE_1__* cam_cache; struct cam_ctl_t cam_ctl; } ;
struct adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  key; int /*<<< orphan*/  mac; int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,size_t*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void write_cam_cache(struct adapter *adapter, u8 id, u16 ctrl, u8 *mac, u8 *key)
{
	struct dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	struct cam_ctl_t *cam_ctl = &dvobj->cam_ctl;

	spin_lock_bh(&cam_ctl->lock);

	dvobj->cam_cache[id].ctrl = ctrl;
	memcpy(dvobj->cam_cache[id].mac, mac, ETH_ALEN);
	memcpy(dvobj->cam_cache[id].key, key, 16);

	spin_unlock_bh(&cam_ctl->lock);
}