#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * ptr; } ;
struct radeon_cs_parser {TYPE_1__ ib; } ;
struct radeon_cs_packet {unsigned int idx; int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,unsigned int,int /*<<< orphan*/  volatile) ; 

void radeon_cs_dump_packet(struct radeon_cs_parser *p,
			   struct radeon_cs_packet *pkt)
{
	volatile uint32_t *ib;
	unsigned i;
	unsigned idx;

	ib = p->ib.ptr;
	idx = pkt->idx;
	for (i = 0; i <= (pkt->count + 1); i++, idx++)
		DRM_INFO("ib[%d]=0x%08X\n", idx, ib[idx]);
}