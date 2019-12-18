#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dc_plane_state {TYPE_3__* blend_tf; TYPE_5__* lut3d_func; TYPE_2__* in_shaper_func; TYPE_1__* in_transfer_func; TYPE_4__* gamma_correction; struct dc_context* ctx; } ;
struct dc_context {int dummy; } ;
struct TYPE_10__ {struct dc_context* ctx; } ;
struct TYPE_9__ {int is_identity; } ;
struct TYPE_8__ {struct dc_context* ctx; void* type; } ;
struct TYPE_7__ {struct dc_context* ctx; void* type; } ;
struct TYPE_6__ {struct dc_context* ctx; void* type; } ;

/* Variables and functions */
 void* TF_TYPE_BYPASS ; 
 TYPE_5__* dc_create_3dlut_func () ; 
 TYPE_4__* dc_create_gamma () ; 
 void* dc_create_transfer_func () ; 

__attribute__((used)) static void construct(struct dc_context *ctx, struct dc_plane_state *plane_state)
{
	plane_state->ctx = ctx;

	plane_state->gamma_correction = dc_create_gamma();
	if (plane_state->gamma_correction != NULL)
		plane_state->gamma_correction->is_identity = true;

	plane_state->in_transfer_func = dc_create_transfer_func();
	if (plane_state->in_transfer_func != NULL) {
		plane_state->in_transfer_func->type = TF_TYPE_BYPASS;
		plane_state->in_transfer_func->ctx = ctx;
	}
#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
	plane_state->in_shaper_func = dc_create_transfer_func();
	if (plane_state->in_shaper_func != NULL) {
		plane_state->in_shaper_func->type = TF_TYPE_BYPASS;
		plane_state->in_shaper_func->ctx = ctx;
	}

	plane_state->lut3d_func = dc_create_3dlut_func();
	if (plane_state->lut3d_func != NULL) {
		plane_state->lut3d_func->ctx = ctx;
	}
	plane_state->blend_tf = dc_create_transfer_func();
	if (plane_state->blend_tf != NULL) {
		plane_state->blend_tf->type = TF_TYPE_BYPASS;
		plane_state->blend_tf->ctx = ctx;
	}

#endif
}