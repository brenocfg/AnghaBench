#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iw_cm_id {int /*<<< orphan*/  (* rem_ref ) (struct iw_cm_id*) ;scalar_t__ provider_data; } ;
struct TYPE_5__ {TYPE_1__* api; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* stop_listener ) (TYPE_2__*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NES_DBG_CM ; 
 TYPE_2__* g_cm_core ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct iw_cm_id*) ; 

int nes_destroy_listen(struct iw_cm_id *cm_id)
{
	if (cm_id->provider_data)
		g_cm_core->api->stop_listener(g_cm_core, cm_id->provider_data);
	else
		nes_debug(NES_DBG_CM, "cm_id->provider_data was NULL\n");

	cm_id->rem_ref(cm_id);

	return 0;
}