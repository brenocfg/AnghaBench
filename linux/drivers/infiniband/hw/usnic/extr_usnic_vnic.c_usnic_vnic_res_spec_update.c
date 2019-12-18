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
typedef  int /*<<< orphan*/  u16 ;
struct usnic_vnic_res_spec {TYPE_1__* resources; } ;
typedef  enum usnic_vnic_res_type { ____Placeholder_usnic_vnic_res_type } usnic_vnic_res_type ;
struct TYPE_2__ {int type; int /*<<< orphan*/  cnt; } ;

/* Variables and functions */
 int USNIC_VNIC_RES_TYPE_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

void usnic_vnic_res_spec_update(struct usnic_vnic_res_spec *spec,
				enum usnic_vnic_res_type trgt_type,
				u16 cnt)
{
	int i;

	for (i = 0; i < USNIC_VNIC_RES_TYPE_MAX; i++) {
		if (spec->resources[i].type == trgt_type) {
			spec->resources[i].cnt = cnt;
			return;
		}
	}

	WARN_ON(1);
}