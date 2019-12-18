#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  size_t hazard_t ;
struct TYPE_4__ {scalar_t__ unfinished; int z_addr; int d_addr; int** t_addr; size_t texture; int* tex_level_lo; int* tex_level_hi; int** pitch; int* tex_npot; int** height; int agp_texture; int* tex_palette_size; int vertex_count; int multitex; } ;
typedef  TYPE_1__ drm_via_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int HALCYON_FIRECMD ; 
 int HALCYON_FIREMASK ; 
 int HALCYON_HEADER1 ; 
 int HALCYON_HEADER1MASK ; 
 int HALCYON_HEADER2 ; 
 int HC_DUMMY ; 
 int HC_HTXnEnPit_MASK ; 
 int HC_HTXnLnPitE_MASK ; 
 int HC_HTXnLnPitE_SHIFT ; 
 int HC_HTXnLnPit_MASK ; 
 int HC_SubA_HTXnL0Pit ; 
#define  check_destination_addr0 152 
#define  check_destination_addr1 151 
#define  check_destination_addr_mode 150 
#define  check_for_dd 149 
#define  check_for_dummy 148 
#define  check_for_fire 147 
#define  check_for_header1 146 
#define  check_for_header1_err 145 
#define  check_for_header2 144 
#define  check_for_header2_err 143 
#define  check_for_vertex_count 142 
#define  check_number_texunits 141 
#define  check_texture_addr0 140 
#define  check_texture_addr1 139 
#define  check_texture_addr2 138 
#define  check_texture_addr3 137 
#define  check_texture_addr4 136 
#define  check_texture_addr5 135 
#define  check_texture_addr6 134 
#define  check_texture_addr7 133 
#define  check_texture_addr8 132 
#define  check_texture_addr_mode 131 
#define  check_z_buffer_addr0 130 
#define  check_z_buffer_addr1 129 
#define  check_z_buffer_addr_mode 128 
 void* dest_address ; 
 int finish_current_sequence (TYPE_1__*) ; 
 scalar_t__* seqs ; 
 void* tex_address ; 
 void* z_address ; 

__attribute__((used)) static __inline__ int
investigate_hazard(uint32_t cmd, hazard_t hz, drm_via_state_t *cur_seq)
{
	register uint32_t tmp, *tmp_addr;

	if (cur_seq->unfinished && (cur_seq->unfinished != seqs[hz])) {
		int ret;
		if ((ret = finish_current_sequence(cur_seq)))
			return ret;
	}

	switch (hz) {
	case check_for_header2:
		if (cmd == HALCYON_HEADER2)
			return 1;
		return 0;
	case check_for_header1:
		if ((cmd & HALCYON_HEADER1MASK) == HALCYON_HEADER1)
			return 1;
		return 0;
	case check_for_header2_err:
		if (cmd == HALCYON_HEADER2)
			return 1;
		DRM_ERROR("Illegal DMA HALCYON_HEADER2 command\n");
		break;
	case check_for_header1_err:
		if ((cmd & HALCYON_HEADER1MASK) == HALCYON_HEADER1)
			return 1;
		DRM_ERROR("Illegal DMA HALCYON_HEADER1 command\n");
		break;
	case check_for_fire:
		if ((cmd & HALCYON_FIREMASK) == HALCYON_FIRECMD)
			return 1;
		DRM_ERROR("Illegal DMA HALCYON_FIRECMD command\n");
		break;
	case check_for_dummy:
		if (HC_DUMMY == cmd)
			return 0;
		DRM_ERROR("Illegal DMA HC_DUMMY command\n");
		break;
	case check_for_dd:
		if (0xdddddddd == cmd)
			return 0;
		DRM_ERROR("Illegal DMA 0xdddddddd command\n");
		break;
	case check_z_buffer_addr0:
		cur_seq->unfinished = z_address;
		cur_seq->z_addr = (cur_seq->z_addr & 0xFF000000) |
		    (cmd & 0x00FFFFFF);
		return 0;
	case check_z_buffer_addr1:
		cur_seq->unfinished = z_address;
		cur_seq->z_addr = (cur_seq->z_addr & 0x00FFFFFF) |
		    ((cmd & 0xFF) << 24);
		return 0;
	case check_z_buffer_addr_mode:
		cur_seq->unfinished = z_address;
		if ((cmd & 0x0000C000) == 0)
			return 0;
		DRM_ERROR("Attempt to place Z buffer in system memory\n");
		return 2;
	case check_destination_addr0:
		cur_seq->unfinished = dest_address;
		cur_seq->d_addr = (cur_seq->d_addr & 0xFF000000) |
		    (cmd & 0x00FFFFFF);
		return 0;
	case check_destination_addr1:
		cur_seq->unfinished = dest_address;
		cur_seq->d_addr = (cur_seq->d_addr & 0x00FFFFFF) |
		    ((cmd & 0xFF) << 24);
		return 0;
	case check_destination_addr_mode:
		cur_seq->unfinished = dest_address;
		if ((cmd & 0x0000C000) == 0)
			return 0;
		DRM_ERROR
		    ("Attempt to place 3D drawing buffer in system memory\n");
		return 2;
	case check_texture_addr0:
		cur_seq->unfinished = tex_address;
		tmp = (cmd >> 24);
		tmp_addr = &cur_seq->t_addr[cur_seq->texture][tmp];
		*tmp_addr = (*tmp_addr & 0xFF000000) | (cmd & 0x00FFFFFF);
		return 0;
	case check_texture_addr1:
		cur_seq->unfinished = tex_address;
		tmp = ((cmd >> 24) - 0x20);
		tmp += tmp << 1;
		tmp_addr = &cur_seq->t_addr[cur_seq->texture][tmp];
		*tmp_addr = (*tmp_addr & 0x00FFFFFF) | ((cmd & 0xFF) << 24);
		tmp_addr++;
		*tmp_addr = (*tmp_addr & 0x00FFFFFF) | ((cmd & 0xFF00) << 16);
		tmp_addr++;
		*tmp_addr = (*tmp_addr & 0x00FFFFFF) | ((cmd & 0xFF0000) << 8);
		return 0;
	case check_texture_addr2:
		cur_seq->unfinished = tex_address;
		cur_seq->tex_level_lo[tmp = cur_seq->texture] = cmd & 0x3F;
		cur_seq->tex_level_hi[tmp] = (cmd & 0xFC0) >> 6;
		return 0;
	case check_texture_addr3:
		cur_seq->unfinished = tex_address;
		tmp = ((cmd >> 24) - HC_SubA_HTXnL0Pit);
		if (tmp == 0 &&
		    (cmd & HC_HTXnEnPit_MASK)) {
			cur_seq->pitch[cur_seq->texture][tmp] =
				(cmd & HC_HTXnLnPit_MASK);
			cur_seq->tex_npot[cur_seq->texture] = 1;
		} else {
			cur_seq->pitch[cur_seq->texture][tmp] =
				(cmd & HC_HTXnLnPitE_MASK) >> HC_HTXnLnPitE_SHIFT;
			cur_seq->tex_npot[cur_seq->texture] = 0;
			if (cmd & 0x000FFFFF) {
				DRM_ERROR
					("Unimplemented texture level 0 pitch mode.\n");
				return 2;
			}
		}
		return 0;
	case check_texture_addr4:
		cur_seq->unfinished = tex_address;
		tmp_addr = &cur_seq->t_addr[cur_seq->texture][9];
		*tmp_addr = (*tmp_addr & 0x00FFFFFF) | ((cmd & 0xFF) << 24);
		return 0;
	case check_texture_addr5:
	case check_texture_addr6:
		cur_seq->unfinished = tex_address;
		/*
		 * Texture width. We don't care since we have the pitch.
		 */
		return 0;
	case check_texture_addr7:
		cur_seq->unfinished = tex_address;
		tmp_addr = &(cur_seq->height[cur_seq->texture][0]);
		tmp_addr[5] = 1 << ((cmd & 0x00F00000) >> 20);
		tmp_addr[4] = 1 << ((cmd & 0x000F0000) >> 16);
		tmp_addr[3] = 1 << ((cmd & 0x0000F000) >> 12);
		tmp_addr[2] = 1 << ((cmd & 0x00000F00) >> 8);
		tmp_addr[1] = 1 << ((cmd & 0x000000F0) >> 4);
		tmp_addr[0] = 1 << (cmd & 0x0000000F);
		return 0;
	case check_texture_addr8:
		cur_seq->unfinished = tex_address;
		tmp_addr = &(cur_seq->height[cur_seq->texture][0]);
		tmp_addr[9] = 1 << ((cmd & 0x0000F000) >> 12);
		tmp_addr[8] = 1 << ((cmd & 0x00000F00) >> 8);
		tmp_addr[7] = 1 << ((cmd & 0x000000F0) >> 4);
		tmp_addr[6] = 1 << (cmd & 0x0000000F);
		return 0;
	case check_texture_addr_mode:
		cur_seq->unfinished = tex_address;
		if (2 == (tmp = cmd & 0x00000003)) {
			DRM_ERROR
			    ("Attempt to fetch texture from system memory.\n");
			return 2;
		}
		cur_seq->agp_texture = (tmp == 3);
		cur_seq->tex_palette_size[cur_seq->texture] =
		    (cmd >> 16) & 0x000000007;
		return 0;
	case check_for_vertex_count:
		cur_seq->vertex_count = cmd & 0x0000FFFF;
		return 0;
	case check_number_texunits:
		cur_seq->multitex = (cmd >> 3) & 1;
		return 0;
	default:
		DRM_ERROR("Illegal DMA data: 0x%x\n", cmd);
		return 2;
	}
	return 2;
}