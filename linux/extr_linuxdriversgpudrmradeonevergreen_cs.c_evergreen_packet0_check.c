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
struct radeon_cs_parser {int dummy; } ;
struct radeon_cs_packet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int,unsigned int) ; 
 int EINVAL ; 
#define  EVERGREEN_VLINE_START_END 128 
 int evergreen_cs_packet_parse_vline (struct radeon_cs_parser*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int evergreen_packet0_check(struct radeon_cs_parser *p,
				   struct radeon_cs_packet *pkt,
				   unsigned idx, unsigned reg)
{
	int r;

	switch (reg) {
	case EVERGREEN_VLINE_START_END:
		r = evergreen_cs_packet_parse_vline(p);
		if (r) {
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
					idx, reg);
			return r;
		}
		break;
	default:
		pr_err("Forbidden register 0x%04X in cs at %d\n", reg, idx);
		return -EINVAL;
	}
	return 0;
}