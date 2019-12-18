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
typedef  scalar_t__ const uint32_t ;
struct radeon_cs_parser {int dummy; } ;

/* Variables and functions */
#define  EVERGREEN_CRTC0_REGISTER_OFFSET 135 
#define  EVERGREEN_CRTC1_REGISTER_OFFSET 134 
#define  EVERGREEN_CRTC2_REGISTER_OFFSET 133 
#define  EVERGREEN_CRTC3_REGISTER_OFFSET 132 
#define  EVERGREEN_CRTC4_REGISTER_OFFSET 131 
#define  EVERGREEN_CRTC5_REGISTER_OFFSET 130 
#define  EVERGREEN_VLINE_START_END 129 
#define  EVERGREEN_VLINE_STATUS 128 
 int r600_cs_common_vline_parse (struct radeon_cs_parser*,scalar_t__ const*,scalar_t__ const*) ; 

__attribute__((used)) static int evergreen_cs_packet_parse_vline(struct radeon_cs_parser *p)
{

	static uint32_t vline_start_end[6] = {
		EVERGREEN_VLINE_START_END + EVERGREEN_CRTC0_REGISTER_OFFSET,
		EVERGREEN_VLINE_START_END + EVERGREEN_CRTC1_REGISTER_OFFSET,
		EVERGREEN_VLINE_START_END + EVERGREEN_CRTC2_REGISTER_OFFSET,
		EVERGREEN_VLINE_START_END + EVERGREEN_CRTC3_REGISTER_OFFSET,
		EVERGREEN_VLINE_START_END + EVERGREEN_CRTC4_REGISTER_OFFSET,
		EVERGREEN_VLINE_START_END + EVERGREEN_CRTC5_REGISTER_OFFSET
	};
	static uint32_t vline_status[6] = {
		EVERGREEN_VLINE_STATUS + EVERGREEN_CRTC0_REGISTER_OFFSET,
		EVERGREEN_VLINE_STATUS + EVERGREEN_CRTC1_REGISTER_OFFSET,
		EVERGREEN_VLINE_STATUS + EVERGREEN_CRTC2_REGISTER_OFFSET,
		EVERGREEN_VLINE_STATUS + EVERGREEN_CRTC3_REGISTER_OFFSET,
		EVERGREEN_VLINE_STATUS + EVERGREEN_CRTC4_REGISTER_OFFSET,
		EVERGREEN_VLINE_STATUS + EVERGREEN_CRTC5_REGISTER_OFFSET
	};

	return r600_cs_common_vline_parse(p, vline_start_end, vline_status);
}