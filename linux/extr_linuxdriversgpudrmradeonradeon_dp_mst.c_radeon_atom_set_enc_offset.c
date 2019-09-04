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

/* Variables and functions */
#define  EVERGREEN_CRTC0_REGISTER_OFFSET 133 
#define  EVERGREEN_CRTC1_REGISTER_OFFSET 132 
#define  EVERGREEN_CRTC2_REGISTER_OFFSET 131 
#define  EVERGREEN_CRTC3_REGISTER_OFFSET 130 
#define  EVERGREEN_CRTC4_REGISTER_OFFSET 129 
#define  EVERGREEN_CRTC5_REGISTER_OFFSET 128 

__attribute__((used)) static int radeon_atom_set_enc_offset(int id)
{
	static const int offsets[] = { EVERGREEN_CRTC0_REGISTER_OFFSET,
				       EVERGREEN_CRTC1_REGISTER_OFFSET,
				       EVERGREEN_CRTC2_REGISTER_OFFSET,
				       EVERGREEN_CRTC3_REGISTER_OFFSET,
				       EVERGREEN_CRTC4_REGISTER_OFFSET,
				       EVERGREEN_CRTC5_REGISTER_OFFSET,
				       0x13830 - 0x7030 };

	return offsets[id];
}