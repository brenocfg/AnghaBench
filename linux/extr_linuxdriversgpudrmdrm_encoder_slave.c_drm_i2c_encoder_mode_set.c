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
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* mode_set ) (struct drm_encoder*,struct drm_display_mode*,struct drm_display_mode*) ;} ;

/* Variables and functions */
 TYPE_1__* get_slave_funcs (struct drm_encoder*) ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*,struct drm_display_mode*,struct drm_display_mode*) ; 

void drm_i2c_encoder_mode_set(struct drm_encoder *encoder,
		struct drm_display_mode *mode,
		struct drm_display_mode *adjusted_mode)
{
	get_slave_funcs(encoder)->mode_set(encoder, mode, adjusted_mode);
}