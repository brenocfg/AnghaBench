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
typedef  int /*<<< orphan*/  verifier_state_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int VIA_VIDEOMASK ; 
 scalar_t__ eat_words (int const**,int const*,int) ; 
 int /*<<< orphan*/  state_command ; 
 int /*<<< orphan*/  state_error ; 
 scalar_t__ verify_mmio_address (int) ; 
 scalar_t__ verify_video_tail (int const**,int const*,int) ; 

__attribute__((used)) static __inline__ verifier_state_t
via_check_vheader5(uint32_t const **buffer, const uint32_t *buf_end)
{
	uint32_t data;
	const uint32_t *buf = *buffer;

	if (buf_end - buf < 4) {
		DRM_ERROR("Illegal termination of video header5 command\n");
		return state_error;
	}

	data = *buf++ & ~VIA_VIDEOMASK;
	if (verify_mmio_address(data))
		return state_error;

	data = *buf++;
	if (*buf++ != 0x00F50000) {
		DRM_ERROR("Illegal header5 header data\n");
		return state_error;
	}
	if (*buf++ != 0x00000000) {
		DRM_ERROR("Illegal header5 header data\n");
		return state_error;
	}
	if (eat_words(&buf, buf_end, data))
		return state_error;
	if ((data & 3) && verify_video_tail(&buf, buf_end, 4 - (data & 3)))
		return state_error;
	*buffer = buf;
	return state_command;

}