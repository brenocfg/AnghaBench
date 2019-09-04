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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  samplerate; } ;
struct vc4_hdmi {TYPE_2__ audio; int /*<<< orphan*/  hsm_clock; TYPE_1__* encoder; } ;
struct vc4_dev {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_3__ {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HD_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VC4_HD_MAI_SMP ; 
 int /*<<< orphan*/  VC4_HD_MAI_SMP_M ; 
 int VC4_HD_MAI_SMP_M_MASK ; 
 int VC4_HD_MAI_SMP_M_SHIFT ; 
 int /*<<< orphan*/  VC4_HD_MAI_SMP_N ; 
 int VC4_HD_MAI_SMP_N_MASK ; 
 int VC4_HD_MAI_SMP_N_SHIFT ; 
 int VC4_SET_FIELD (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rational_best_approximation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned long*,unsigned long*) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

__attribute__((used)) static void vc4_hdmi_audio_set_mai_clock(struct vc4_hdmi *hdmi)
{
	struct drm_device *drm = hdmi->encoder->dev;
	struct vc4_dev *vc4 = to_vc4_dev(drm);
	u32 hsm_clock = clk_get_rate(hdmi->hsm_clock);
	unsigned long n, m;

	rational_best_approximation(hsm_clock, hdmi->audio.samplerate,
				    VC4_HD_MAI_SMP_N_MASK >>
				    VC4_HD_MAI_SMP_N_SHIFT,
				    (VC4_HD_MAI_SMP_M_MASK >>
				     VC4_HD_MAI_SMP_M_SHIFT) + 1,
				    &n, &m);

	HD_WRITE(VC4_HD_MAI_SMP,
		 VC4_SET_FIELD(n, VC4_HD_MAI_SMP_N) |
		 VC4_SET_FIELD(m - 1, VC4_HD_MAI_SMP_M));
}