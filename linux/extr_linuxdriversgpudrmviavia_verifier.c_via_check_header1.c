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
 int HALCYON_HEADER1 ; 
 int HALCYON_HEADER1MASK ; 
 int /*<<< orphan*/  state_command ; 
 int /*<<< orphan*/  state_error ; 

__attribute__((used)) static __inline__ verifier_state_t
via_check_header1(uint32_t const **buffer, const uint32_t * buf_end)
{
	uint32_t cmd;
	const uint32_t *buf = *buffer;
	verifier_state_t ret = state_command;

	while (buf < buf_end) {
		cmd = *buf;
		if ((cmd > ((0x3FF >> 2) | HALCYON_HEADER1)) &&
		    (cmd < ((0xC00 >> 2) | HALCYON_HEADER1))) {
			if ((cmd & HALCYON_HEADER1MASK) != HALCYON_HEADER1)
				break;
			DRM_ERROR("Invalid HALCYON_HEADER1 command. "
				  "Attempt to access 3D- or command burst area.\n");
			ret = state_error;
			break;
		} else if (cmd > ((0xCFF >> 2) | HALCYON_HEADER1)) {
			if ((cmd & HALCYON_HEADER1MASK) != HALCYON_HEADER1)
				break;
			DRM_ERROR("Invalid HALCYON_HEADER1 command. "
				  "Attempt to access VGA registers.\n");
			ret = state_error;
			break;
		} else {
			buf += 2;
		}
	}
	*buffer = buf;
	return ret;
}