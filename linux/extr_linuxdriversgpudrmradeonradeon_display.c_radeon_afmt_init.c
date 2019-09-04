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
typedef  int uint32_t ;
struct TYPE_4__ {TYPE_1__** afmt; } ;
struct radeon_device {scalar_t__ family; TYPE_2__ mode_info; } ;
struct radeon_afmt {int dummy; } ;
struct TYPE_3__ {int offset; int id; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 scalar_t__ ASIC_IS_DCE2 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE3 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE41 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE5 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE6 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE8 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_NODCE (struct radeon_device*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CHIP_R600 ; 
 int DCE2_HDMI_OFFSET0 ; 
 int DCE2_HDMI_OFFSET1 ; 
 int DCE3_HDMI_OFFSET0 ; 
 int DCE3_HDMI_OFFSET1 ; 
#define  EVERGREEN_CRTC0_REGISTER_OFFSET 133 
#define  EVERGREEN_CRTC1_REGISTER_OFFSET 132 
#define  EVERGREEN_CRTC2_REGISTER_OFFSET 131 
#define  EVERGREEN_CRTC3_REGISTER_OFFSET 130 
#define  EVERGREEN_CRTC4_REGISTER_OFFSET 129 
#define  EVERGREEN_CRTC5_REGISTER_OFFSET 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RADEON_MAX_AFMT_BLOCKS ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radeon_afmt_init(struct radeon_device *rdev)
{
	int i;

	for (i = 0; i < RADEON_MAX_AFMT_BLOCKS; i++)
		rdev->mode_info.afmt[i] = NULL;

	if (ASIC_IS_NODCE(rdev)) {
		/* nothing to do */
	} else if (ASIC_IS_DCE4(rdev)) {
		static uint32_t eg_offsets[] = {
			EVERGREEN_CRTC0_REGISTER_OFFSET,
			EVERGREEN_CRTC1_REGISTER_OFFSET,
			EVERGREEN_CRTC2_REGISTER_OFFSET,
			EVERGREEN_CRTC3_REGISTER_OFFSET,
			EVERGREEN_CRTC4_REGISTER_OFFSET,
			EVERGREEN_CRTC5_REGISTER_OFFSET,
			0x13830 - 0x7030,
		};
		int num_afmt;

		/* DCE8 has 7 audio blocks tied to DIG encoders */
		/* DCE6 has 6 audio blocks tied to DIG encoders */
		/* DCE4/5 has 6 audio blocks tied to DIG encoders */
		/* DCE4.1 has 2 audio blocks tied to DIG encoders */
		if (ASIC_IS_DCE8(rdev))
			num_afmt = 7;
		else if (ASIC_IS_DCE6(rdev))
			num_afmt = 6;
		else if (ASIC_IS_DCE5(rdev))
			num_afmt = 6;
		else if (ASIC_IS_DCE41(rdev))
			num_afmt = 2;
		else /* DCE4 */
			num_afmt = 6;

		BUG_ON(num_afmt > ARRAY_SIZE(eg_offsets));
		for (i = 0; i < num_afmt; i++) {
			rdev->mode_info.afmt[i] = kzalloc(sizeof(struct radeon_afmt), GFP_KERNEL);
			if (rdev->mode_info.afmt[i]) {
				rdev->mode_info.afmt[i]->offset = eg_offsets[i];
				rdev->mode_info.afmt[i]->id = i;
			}
		}
	} else if (ASIC_IS_DCE3(rdev)) {
		/* DCE3.x has 2 audio blocks tied to DIG encoders */
		rdev->mode_info.afmt[0] = kzalloc(sizeof(struct radeon_afmt), GFP_KERNEL);
		if (rdev->mode_info.afmt[0]) {
			rdev->mode_info.afmt[0]->offset = DCE3_HDMI_OFFSET0;
			rdev->mode_info.afmt[0]->id = 0;
		}
		rdev->mode_info.afmt[1] = kzalloc(sizeof(struct radeon_afmt), GFP_KERNEL);
		if (rdev->mode_info.afmt[1]) {
			rdev->mode_info.afmt[1]->offset = DCE3_HDMI_OFFSET1;
			rdev->mode_info.afmt[1]->id = 1;
		}
	} else if (ASIC_IS_DCE2(rdev)) {
		/* DCE2 has at least 1 routable audio block */
		rdev->mode_info.afmt[0] = kzalloc(sizeof(struct radeon_afmt), GFP_KERNEL);
		if (rdev->mode_info.afmt[0]) {
			rdev->mode_info.afmt[0]->offset = DCE2_HDMI_OFFSET0;
			rdev->mode_info.afmt[0]->id = 0;
		}
		/* r6xx has 2 routable audio blocks */
		if (rdev->family >= CHIP_R600) {
			rdev->mode_info.afmt[1] = kzalloc(sizeof(struct radeon_afmt), GFP_KERNEL);
			if (rdev->mode_info.afmt[1]) {
				rdev->mode_info.afmt[1]->offset = DCE2_HDMI_OFFSET1;
				rdev->mode_info.afmt[1]->id = 1;
			}
		}
	}
}