#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sti_tvout {int dummy; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TVO_VIP_HDMI ; 
 struct sti_tvout* to_sti_tvout (struct drm_encoder*) ; 
 int /*<<< orphan*/  tvout_write (struct sti_tvout*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sti_hdmi_encoder_disable(struct drm_encoder *encoder)
{
	struct sti_tvout *tvout = to_sti_tvout(encoder);

	/* reset VIP register */
	tvout_write(tvout, 0x0, TVO_VIP_HDMI);
}