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
struct radeon_cs_parser {int idx; TYPE_1__* chunk_ib; int /*<<< orphan*/ * chunk_relocs; } ;
struct radeon_cs_packet {int type; int /*<<< orphan*/  count; } ;
struct TYPE_2__ {int length_dw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
#define  RADEON_PACKET_TYPE0 129 
#define  RADEON_PACKET_TYPE2 128 
 int radeon_cs_packet_parse (struct radeon_cs_parser*,struct radeon_cs_packet*,int) ; 
 int radeon_uvd_cs_reg (struct radeon_cs_parser*,struct radeon_cs_packet*,int*,int*,unsigned int*,int*) ; 

int radeon_uvd_cs_parse(struct radeon_cs_parser *p)
{
	struct radeon_cs_packet pkt;
	int r, data0 = 0, data1 = 0;

	/* does the IB has a msg command */
	bool has_msg_cmd = false;

	/* minimum buffer sizes */
	unsigned buf_sizes[] = {
		[0x00000000]	=	2048,
		[0x00000001]	=	32 * 1024 * 1024,
		[0x00000002]	=	2048 * 1152 * 3,
		[0x00000003]	=	2048,
	};

	if (p->chunk_ib->length_dw % 16) {
		DRM_ERROR("UVD IB length (%d) not 16 dwords aligned!\n",
			  p->chunk_ib->length_dw);
		return -EINVAL;
	}

	if (p->chunk_relocs == NULL) {
		DRM_ERROR("No relocation chunk !\n");
		return -EINVAL;
	}


	do {
		r = radeon_cs_packet_parse(p, &pkt, p->idx);
		if (r)
			return r;
		switch (pkt.type) {
		case RADEON_PACKET_TYPE0:
			r = radeon_uvd_cs_reg(p, &pkt, &data0, &data1,
					      buf_sizes, &has_msg_cmd);
			if (r)
				return r;
			break;
		case RADEON_PACKET_TYPE2:
			p->idx += pkt.count + 2;
			break;
		default:
			DRM_ERROR("Unknown packet type %d !\n", pkt.type);
			return -EINVAL;
		}
	} while (p->idx < p->chunk_ib->length_dw);

	if (!has_msg_cmd) {
		DRM_ERROR("UVD-IBs need a msg command!\n");
		return -EINVAL;
	}

	return 0;
}