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
struct link_encoder {TYPE_1__* funcs; } ;
struct dc_link {struct link_encoder* link_enc; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_hpd ) (struct link_encoder*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct link_encoder*) ; 

void dc_link_dp_enable_hpd(const struct dc_link *link)
{
	struct link_encoder *encoder = link->link_enc;

	if (encoder != NULL && encoder->funcs->enable_hpd != NULL)
		encoder->funcs->enable_hpd(encoder);
}