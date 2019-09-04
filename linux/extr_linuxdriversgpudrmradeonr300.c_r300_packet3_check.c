#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u32 ;
struct TYPE_3__ {int* ptr; } ;
struct radeon_cs_parser {int /*<<< orphan*/  filp; TYPE_2__* rdev; scalar_t__ track; TYPE_1__ ib; } ;
struct radeon_cs_packet {int idx; int opcode; int /*<<< orphan*/  count; } ;
struct radeon_bo_list {int /*<<< orphan*/  robj; int /*<<< orphan*/  gpu_offset; } ;
struct r100_cs_track {int vap_vf_cntl; int /*<<< orphan*/  immd_dwords; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmask_filp; int /*<<< orphan*/  hyperz_filp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
#define  PACKET3_3D_CLEAR_CMASK 139 
#define  PACKET3_3D_CLEAR_HIZ 138 
#define  PACKET3_3D_CLEAR_ZMASK 137 
#define  PACKET3_3D_DRAW_IMMD 136 
#define  PACKET3_3D_DRAW_IMMD_2 135 
#define  PACKET3_3D_DRAW_INDX 134 
#define  PACKET3_3D_DRAW_INDX_2 133 
#define  PACKET3_3D_DRAW_VBUF 132 
#define  PACKET3_3D_DRAW_VBUF_2 131 
#define  PACKET3_3D_LOAD_VBPNTR 130 
#define  PACKET3_INDX_BUFFER 129 
#define  PACKET3_NOP 128 
 int r100_cs_track_check (TYPE_2__*,struct r100_cs_track*) ; 
 int r100_cs_track_check_pkt3_indx_buffer (struct radeon_cs_parser*,struct radeon_cs_packet*,int /*<<< orphan*/ ) ; 
 int r100_packet3_load_vbpntr (struct radeon_cs_parser*,struct radeon_cs_packet*,unsigned int) ; 
 int /*<<< orphan*/  radeon_cs_dump_packet (struct radeon_cs_parser*,struct radeon_cs_packet*) ; 
 int radeon_cs_packet_next_reloc (struct radeon_cs_parser*,struct radeon_bo_list**,int /*<<< orphan*/ ) ; 
 int radeon_get_ib_value (struct radeon_cs_parser*,unsigned int) ; 

__attribute__((used)) static int r300_packet3_check(struct radeon_cs_parser *p,
			      struct radeon_cs_packet *pkt)
{
	struct radeon_bo_list *reloc;
	struct r100_cs_track *track;
	volatile uint32_t *ib;
	unsigned idx;
	int r;

	ib = p->ib.ptr;
	idx = pkt->idx + 1;
	track = (struct r100_cs_track *)p->track;
	switch(pkt->opcode) {
	case PACKET3_3D_LOAD_VBPNTR:
		r = r100_packet3_load_vbpntr(p, pkt, idx);
		if (r)
			return r;
		break;
	case PACKET3_INDX_BUFFER:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		if (r) {
			DRM_ERROR("No reloc for packet3 %d\n", pkt->opcode);
			radeon_cs_dump_packet(p, pkt);
			return r;
		}
		ib[idx+1] = radeon_get_ib_value(p, idx + 1) + ((u32)reloc->gpu_offset);
		r = r100_cs_track_check_pkt3_indx_buffer(p, pkt, reloc->robj);
		if (r) {
			return r;
		}
		break;
	/* Draw packet */
	case PACKET3_3D_DRAW_IMMD:
		/* Number of dwords is vtx_size * (num_vertices - 1)
		 * PRIM_WALK must be equal to 3 vertex data in embedded
		 * in cmd stream */
		if (((radeon_get_ib_value(p, idx + 1) >> 4) & 0x3) != 3) {
			DRM_ERROR("PRIM_WALK must be 3 for IMMD draw\n");
			return -EINVAL;
		}
		track->vap_vf_cntl = radeon_get_ib_value(p, idx + 1);
		track->immd_dwords = pkt->count - 1;
		r = r100_cs_track_check(p->rdev, track);
		if (r) {
			return r;
		}
		break;
	case PACKET3_3D_DRAW_IMMD_2:
		/* Number of dwords is vtx_size * (num_vertices - 1)
		 * PRIM_WALK must be equal to 3 vertex data in embedded
		 * in cmd stream */
		if (((radeon_get_ib_value(p, idx) >> 4) & 0x3) != 3) {
			DRM_ERROR("PRIM_WALK must be 3 for IMMD draw\n");
			return -EINVAL;
		}
		track->vap_vf_cntl = radeon_get_ib_value(p, idx);
		track->immd_dwords = pkt->count;
		r = r100_cs_track_check(p->rdev, track);
		if (r) {
			return r;
		}
		break;
	case PACKET3_3D_DRAW_VBUF:
		track->vap_vf_cntl = radeon_get_ib_value(p, idx + 1);
		r = r100_cs_track_check(p->rdev, track);
		if (r) {
			return r;
		}
		break;
	case PACKET3_3D_DRAW_VBUF_2:
		track->vap_vf_cntl = radeon_get_ib_value(p, idx);
		r = r100_cs_track_check(p->rdev, track);
		if (r) {
			return r;
		}
		break;
	case PACKET3_3D_DRAW_INDX:
		track->vap_vf_cntl = radeon_get_ib_value(p, idx + 1);
		r = r100_cs_track_check(p->rdev, track);
		if (r) {
			return r;
		}
		break;
	case PACKET3_3D_DRAW_INDX_2:
		track->vap_vf_cntl = radeon_get_ib_value(p, idx);
		r = r100_cs_track_check(p->rdev, track);
		if (r) {
			return r;
		}
		break;
	case PACKET3_3D_CLEAR_HIZ:
	case PACKET3_3D_CLEAR_ZMASK:
		if (p->rdev->hyperz_filp != p->filp)
			return -EINVAL;
		break;
	case PACKET3_3D_CLEAR_CMASK:
		if (p->rdev->cmask_filp != p->filp)
			return -EINVAL;
		break;
	case PACKET3_NOP:
		break;
	default:
		DRM_ERROR("Packet3 opcode %x not supported\n", pkt->opcode);
		return -EINVAL;
	}
	return 0;
}