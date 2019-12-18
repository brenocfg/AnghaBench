#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dc_link {int sink_count; scalar_t__* remote_sinks; scalar_t__ local_sink; TYPE_2__* link_enc; scalar_t__ ddc; int /*<<< orphan*/ * hpd_gpio; } ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* destroy ) (TYPE_2__**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dal_ddc_service_destroy (scalar_t__*) ; 
 int /*<<< orphan*/  dal_gpio_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dal_gpio_destroy_irq (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dc_sink_release (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**) ; 

__attribute__((used)) static void destruct(struct dc_link *link)
{
	int i;

	if (link->hpd_gpio != NULL) {
		dal_gpio_close(link->hpd_gpio);
		dal_gpio_destroy_irq(&link->hpd_gpio);
		link->hpd_gpio = NULL;
	}

	if (link->ddc)
		dal_ddc_service_destroy(&link->ddc);

	if(link->link_enc)
		link->link_enc->funcs->destroy(&link->link_enc);

	if (link->local_sink)
		dc_sink_release(link->local_sink);

	for (i = 0; i < link->sink_count; ++i)
		dc_sink_release(link->remote_sinks[i]);
}