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
struct link_training_settings {int dummy; } ;
struct link_encoder {TYPE_1__* funcs; } ;
struct dc_link {struct link_encoder* link_enc; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dp_set_lane_settings ) (struct link_encoder*,struct link_training_settings const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct link_encoder*,struct link_training_settings const*) ; 

void dp_set_hw_lane_settings(
	struct dc_link *link,
	const struct link_training_settings *link_settings)
{
	struct link_encoder *encoder = link->link_enc;

	/* call Encoder to set lane settings */
	encoder->funcs->dp_set_lane_settings(encoder, link_settings);
}