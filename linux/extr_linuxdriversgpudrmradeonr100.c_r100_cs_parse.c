#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct radeon_cs_parser {TYPE_4__* rdev; int /*<<< orphan*/  idx; TYPE_1__* chunk_ib; struct r100_cs_track* track; } ;
struct radeon_cs_packet {int type; scalar_t__ count; } ;
struct r100_cs_track {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  reg_safe_bm_size; int /*<<< orphan*/  reg_safe_bm; } ;
struct TYPE_7__ {TYPE_2__ r100; } ;
struct TYPE_8__ {TYPE_3__ config; int /*<<< orphan*/  family; } ;
struct TYPE_5__ {int /*<<< orphan*/  length_dw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_R200 ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  RADEON_PACKET_TYPE0 130 
#define  RADEON_PACKET_TYPE2 129 
#define  RADEON_PACKET_TYPE3 128 
 struct r100_cs_track* kzalloc (int,int /*<<< orphan*/ ) ; 
 int r100_cs_parse_packet0 (struct radeon_cs_parser*,struct radeon_cs_packet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r100_cs_track_clear (TYPE_4__*,struct r100_cs_track*) ; 
 int /*<<< orphan*/  r100_packet0_check ; 
 int r100_packet3_check (struct radeon_cs_parser*,struct radeon_cs_packet*) ; 
 int /*<<< orphan*/  r200_packet0_check ; 
 int radeon_cs_packet_parse (struct radeon_cs_parser*,struct radeon_cs_packet*,int /*<<< orphan*/ ) ; 

int r100_cs_parse(struct radeon_cs_parser *p)
{
	struct radeon_cs_packet pkt;
	struct r100_cs_track *track;
	int r;

	track = kzalloc(sizeof(*track), GFP_KERNEL);
	if (!track)
		return -ENOMEM;
	r100_cs_track_clear(p->rdev, track);
	p->track = track;
	do {
		r = radeon_cs_packet_parse(p, &pkt, p->idx);
		if (r) {
			return r;
		}
		p->idx += pkt.count + 2;
		switch (pkt.type) {
		case RADEON_PACKET_TYPE0:
			if (p->rdev->family >= CHIP_R200)
				r = r100_cs_parse_packet0(p, &pkt,
					p->rdev->config.r100.reg_safe_bm,
					p->rdev->config.r100.reg_safe_bm_size,
					&r200_packet0_check);
			else
				r = r100_cs_parse_packet0(p, &pkt,
					p->rdev->config.r100.reg_safe_bm,
					p->rdev->config.r100.reg_safe_bm_size,
					&r100_packet0_check);
			break;
		case RADEON_PACKET_TYPE2:
			break;
		case RADEON_PACKET_TYPE3:
			r = r100_packet3_check(p, &pkt);
			break;
		default:
			DRM_ERROR("Unknown packet type %d !\n",
				  pkt.type);
			return -EINVAL;
		}
		if (r)
			return r;
	} while (p->idx < p->chunk_ib->length_dw);
	return 0;
}