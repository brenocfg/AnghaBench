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
struct sti_tvout {int dummy; } ;
struct drm_encoder {TYPE_1__* crtc; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  sti_crtc_is_main (TYPE_1__*) ; 
 struct sti_tvout* to_sti_tvout (struct drm_encoder*) ; 
 int /*<<< orphan*/  tvout_dvo_start (struct sti_tvout*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvout_preformatter_set_matrix (struct sti_tvout*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sti_dvo_encoder_enable(struct drm_encoder *encoder)
{
	struct sti_tvout *tvout = to_sti_tvout(encoder);

	tvout_preformatter_set_matrix(tvout, &encoder->crtc->mode);

	tvout_dvo_start(tvout, sti_crtc_is_main(encoder->crtc));
}