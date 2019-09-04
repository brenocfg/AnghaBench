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
typedef  int /*<<< orphan*/  uint32_t ;
struct radeon_cs_parser {int dummy; } ;

/* Variables and functions */
#define  AVIVO_D1MODE_VLINE_START_END 131 
#define  AVIVO_D1MODE_VLINE_STATUS 130 
#define  AVIVO_D2MODE_VLINE_START_END 129 
#define  AVIVO_D2MODE_VLINE_STATUS 128 
 int r600_cs_common_vline_parse (struct radeon_cs_parser*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r600_cs_packet_parse_vline(struct radeon_cs_parser *p)
{
	static uint32_t vline_start_end[2] = {AVIVO_D1MODE_VLINE_START_END,
					      AVIVO_D2MODE_VLINE_START_END};
	static uint32_t vline_status[2] = {AVIVO_D1MODE_VLINE_STATUS,
					   AVIVO_D2MODE_VLINE_STATUS};

	return r600_cs_common_vline_parse(p, vline_start_end, vline_status);
}