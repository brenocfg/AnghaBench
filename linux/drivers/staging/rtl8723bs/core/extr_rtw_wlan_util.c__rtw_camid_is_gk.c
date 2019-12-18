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
struct cam_ctl_t {int bitmap; } ;
struct dvobj_priv {TYPE_1__* cam_cache; struct cam_ctl_t cam_ctl; } ;
struct adapter {int dummy; } ;
struct TYPE_2__ {int ctrl; } ;

/* Variables and functions */
 int BIT (size_t) ; 
 int BIT6 ; 
 size_t TOTAL_CAM_ENTRY ; 
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 

__attribute__((used)) static bool _rtw_camid_is_gk(struct adapter *adapter, u8 cam_id)
{
	struct dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	struct cam_ctl_t *cam_ctl = &dvobj->cam_ctl;
	bool ret = false;

	if (cam_id >= TOTAL_CAM_ENTRY)
		goto exit;

	if (!(cam_ctl->bitmap & BIT(cam_id)))
		goto exit;

	ret = (dvobj->cam_cache[cam_id].ctrl&BIT6)?true:false;

exit:
	return ret;
}