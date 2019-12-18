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
typedef  scalar_t__ u32 ;
struct radeon_cs_parser {int dummy; } ;
struct radeon_cs_packet {int idx; } ;
struct radeon_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__,scalar_t__) ; 
 int EINVAL ; 
 scalar_t__ radeon_bo_size (struct radeon_bo*) ; 
 scalar_t__ radeon_get_ib_value (struct radeon_cs_parser*,unsigned int) ; 

int r100_cs_track_check_pkt3_indx_buffer(struct radeon_cs_parser *p,
					 struct radeon_cs_packet *pkt,
					 struct radeon_bo *robj)
{
	unsigned idx;
	u32 value;
	idx = pkt->idx + 1;
	value = radeon_get_ib_value(p, idx + 2);
	if ((value + 1) > radeon_bo_size(robj)) {
		DRM_ERROR("[drm] Buffer too small for PACKET3 INDX_BUFFER "
			  "(need %u have %lu) !\n",
			  value + 1,
			  radeon_bo_size(robj));
		return -EINVAL;
	}
	return 0;
}