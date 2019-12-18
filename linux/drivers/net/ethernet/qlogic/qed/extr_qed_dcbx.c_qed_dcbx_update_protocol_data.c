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
struct qed_dcbx_results {TYPE_1__* arr; } ;
struct protocol_dcb_data {int /*<<< orphan*/  dcb_dont_add_vlan0; int /*<<< orphan*/  dcb_tc; int /*<<< orphan*/  dcb_priority; int /*<<< orphan*/  dcb_enable_flag; } ;
typedef  enum dcbx_protocol_type { ____Placeholder_dcbx_protocol_type } dcbx_protocol_type ;
struct TYPE_2__ {int /*<<< orphan*/  dont_add_vlan0; int /*<<< orphan*/  tc; int /*<<< orphan*/  priority; int /*<<< orphan*/  enable; } ;

/* Variables and functions */

__attribute__((used)) static void qed_dcbx_update_protocol_data(struct protocol_dcb_data *p_data,
					  struct qed_dcbx_results *p_src,
					  enum dcbx_protocol_type type)
{
	p_data->dcb_enable_flag = p_src->arr[type].enable;
	p_data->dcb_priority = p_src->arr[type].priority;
	p_data->dcb_tc = p_src->arr[type].tc;
	p_data->dcb_dont_add_vlan0 = p_src->arr[type].dont_add_vlan0;
}