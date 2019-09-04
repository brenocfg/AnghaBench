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
struct dc_plane_state {TYPE_1__* in_transfer_func; TYPE_2__* gamma_correction; struct dc_context* ctx; } ;
struct dc_context {int dummy; } ;
struct TYPE_4__ {int is_identity; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  TF_TYPE_BYPASS ; 
 TYPE_2__* dc_create_gamma () ; 
 TYPE_1__* dc_create_transfer_func () ; 

__attribute__((used)) static void construct(struct dc_context *ctx, struct dc_plane_state *plane_state)
{
	plane_state->ctx = ctx;

	plane_state->gamma_correction = dc_create_gamma();
	plane_state->gamma_correction->is_identity = true;

	plane_state->in_transfer_func = dc_create_transfer_func();
	plane_state->in_transfer_func->type = TF_TYPE_BYPASS;
}