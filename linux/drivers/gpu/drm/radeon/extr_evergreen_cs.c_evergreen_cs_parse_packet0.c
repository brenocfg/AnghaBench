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
struct radeon_cs_packet {int idx; unsigned int reg; unsigned int count; } ;

/* Variables and functions */
 int evergreen_packet0_check (struct radeon_cs_parser*,struct radeon_cs_packet*,unsigned int,unsigned int) ; 

__attribute__((used)) static int evergreen_cs_parse_packet0(struct radeon_cs_parser *p,
				      struct radeon_cs_packet *pkt)
{
	unsigned reg, i;
	unsigned idx;
	int r;

	idx = pkt->idx + 1;
	reg = pkt->reg;
	for (i = 0; i <= pkt->count; i++, idx++, reg += 4) {
		r = evergreen_packet0_check(p, pkt, idx, reg);
		if (r) {
			return r;
		}
	}
	return 0;
}