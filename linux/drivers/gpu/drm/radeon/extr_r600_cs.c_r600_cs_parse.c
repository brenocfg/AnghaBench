#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int length_dw; int /*<<< orphan*/ * ptr; } ;
struct radeon_cs_parser {struct r600_cs_track* track; TYPE_6__ ib; int /*<<< orphan*/  idx; TYPE_5__* chunk_ib; TYPE_4__* rdev; } ;
struct radeon_cs_packet {int type; scalar_t__ count; } ;
struct r600_cs_track {int /*<<< orphan*/  group_size; int /*<<< orphan*/  nbanks; int /*<<< orphan*/  npipes; } ;
struct TYPE_11__ {int /*<<< orphan*/  length_dw; } ;
struct TYPE_8__ {int /*<<< orphan*/  tiling_group_size; int /*<<< orphan*/  tiling_nbanks; int /*<<< orphan*/  tiling_npipes; } ;
struct TYPE_7__ {int /*<<< orphan*/  tiling_group_size; int /*<<< orphan*/  tiling_nbanks; int /*<<< orphan*/  tiling_npipes; } ;
struct TYPE_9__ {TYPE_2__ rv770; TYPE_1__ r600; } ;
struct TYPE_10__ {scalar_t__ family; TYPE_3__ config; } ;

/* Variables and functions */
 scalar_t__ CHIP_RV740 ; 
 scalar_t__ CHIP_RV770 ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  RADEON_PACKET_TYPE0 130 
#define  RADEON_PACKET_TYPE2 129 
#define  RADEON_PACKET_TYPE3 128 
 int /*<<< orphan*/  kfree (struct r600_cs_track*) ; 
 struct r600_cs_track* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_info (char*,int,int /*<<< orphan*/ ) ; 
 int r600_cs_parse_packet0 (struct radeon_cs_parser*,struct radeon_cs_packet*) ; 
 int /*<<< orphan*/  r600_cs_track_init (struct r600_cs_track*) ; 
 int r600_packet3_check (struct radeon_cs_parser*,struct radeon_cs_packet*) ; 
 int radeon_cs_packet_parse (struct radeon_cs_parser*,struct radeon_cs_packet*,int /*<<< orphan*/ ) ; 

int r600_cs_parse(struct radeon_cs_parser *p)
{
	struct radeon_cs_packet pkt;
	struct r600_cs_track *track;
	int r;

	if (p->track == NULL) {
		/* initialize tracker, we are in kms */
		track = kzalloc(sizeof(*track), GFP_KERNEL);
		if (track == NULL)
			return -ENOMEM;
		r600_cs_track_init(track);
		if (p->rdev->family < CHIP_RV770) {
			track->npipes = p->rdev->config.r600.tiling_npipes;
			track->nbanks = p->rdev->config.r600.tiling_nbanks;
			track->group_size = p->rdev->config.r600.tiling_group_size;
		} else if (p->rdev->family <= CHIP_RV740) {
			track->npipes = p->rdev->config.rv770.tiling_npipes;
			track->nbanks = p->rdev->config.rv770.tiling_nbanks;
			track->group_size = p->rdev->config.rv770.tiling_group_size;
		}
		p->track = track;
	}
	do {
		r = radeon_cs_packet_parse(p, &pkt, p->idx);
		if (r) {
			kfree(p->track);
			p->track = NULL;
			return r;
		}
		p->idx += pkt.count + 2;
		switch (pkt.type) {
		case RADEON_PACKET_TYPE0:
			r = r600_cs_parse_packet0(p, &pkt);
			break;
		case RADEON_PACKET_TYPE2:
			break;
		case RADEON_PACKET_TYPE3:
			r = r600_packet3_check(p, &pkt);
			break;
		default:
			DRM_ERROR("Unknown packet type %d !\n", pkt.type);
			kfree(p->track);
			p->track = NULL;
			return -EINVAL;
		}
		if (r) {
			kfree(p->track);
			p->track = NULL;
			return r;
		}
	} while (p->idx < p->chunk_ib->length_dw);
#if 0
	for (r = 0; r < p->ib.length_dw; r++) {
		pr_info("%05d  0x%08X\n", r, p->ib.ptr[r]);
		mdelay(1);
	}
#endif
	kfree(p->track);
	p->track = NULL;
	return 0;
}