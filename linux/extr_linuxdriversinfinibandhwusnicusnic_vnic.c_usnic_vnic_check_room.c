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
struct usnic_vnic_res_spec {TYPE_1__* resources; } ;
struct usnic_vnic {int dummy; } ;
typedef  enum usnic_vnic_res_type { ____Placeholder_usnic_vnic_res_type } usnic_vnic_res_type ;
struct TYPE_2__ {int type; int cnt; } ;

/* Variables and functions */
 int EBUSY ; 
 int USNIC_VNIC_RES_TYPE_EOL ; 
 int USNIC_VNIC_RES_TYPE_MAX ; 
 int usnic_vnic_res_free_cnt (struct usnic_vnic*,int) ; 

int usnic_vnic_check_room(struct usnic_vnic *vnic,
				struct usnic_vnic_res_spec *res_spec)
{
	int i;
	enum usnic_vnic_res_type res_type;
	int res_cnt;

	for (i = 0; i < USNIC_VNIC_RES_TYPE_MAX; i++) {
		res_type = res_spec->resources[i].type;
		res_cnt = res_spec->resources[i].cnt;

		if (res_type == USNIC_VNIC_RES_TYPE_EOL)
			break;

		if (res_cnt > usnic_vnic_res_free_cnt(vnic, res_type))
			return -EBUSY;
	}

	return 0;
}