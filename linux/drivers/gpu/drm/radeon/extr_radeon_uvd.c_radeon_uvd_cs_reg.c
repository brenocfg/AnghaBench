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
struct radeon_cs_parser {int idx; } ;
struct radeon_cs_packet {int count; int reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
#define  UVD_ENGINE_CNTL 132 
#define  UVD_GPCOM_VCPU_CMD 131 
#define  UVD_GPCOM_VCPU_DATA0 130 
#define  UVD_GPCOM_VCPU_DATA1 129 
#define  UVD_NO_OP 128 
 int radeon_uvd_cs_reloc (struct radeon_cs_parser*,int,int,unsigned int*,int*) ; 

__attribute__((used)) static int radeon_uvd_cs_reg(struct radeon_cs_parser *p,
			     struct radeon_cs_packet *pkt,
			     int *data0, int *data1,
			     unsigned buf_sizes[],
			     bool *has_msg_cmd)
{
	int i, r;

	p->idx++;
	for (i = 0; i <= pkt->count; ++i) {
		switch (pkt->reg + i*4) {
		case UVD_GPCOM_VCPU_DATA0:
			*data0 = p->idx;
			break;
		case UVD_GPCOM_VCPU_DATA1:
			*data1 = p->idx;
			break;
		case UVD_GPCOM_VCPU_CMD:
			r = radeon_uvd_cs_reloc(p, *data0, *data1,
						buf_sizes, has_msg_cmd);
			if (r)
				return r;
			break;
		case UVD_ENGINE_CNTL:
		case UVD_NO_OP:
			break;
		default:
			DRM_ERROR("Invalid reg 0x%X!\n",
				  pkt->reg + i*4);
			return -EINVAL;
		}
		p->idx++;
	}
	return 0;
}