#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct vc4_rcl_setup {int next_offset; TYPE_7__* rcl; TYPE_3__* color_write; int /*<<< orphan*/ * zs_write; int /*<<< orphan*/ * msaa_zs_write; int /*<<< orphan*/ * msaa_color_write; scalar_t__ color_read; scalar_t__ zs_read; } ;
struct vc4_exec_info {int ct1ca; int ct1ea; int /*<<< orphan*/  unref_list; struct drm_vc4_submit_cl* args; } ;
struct TYPE_12__ {int /*<<< orphan*/  bits; scalar_t__ offset; } ;
struct TYPE_10__ {int flags; } ;
struct TYPE_9__ {int flags; } ;
struct drm_vc4_submit_cl {scalar_t__ bin_cl_size; int min_x_tile; int min_y_tile; int max_x_tile; int max_y_tile; int flags; TYPE_4__ color_write; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  clear_s; scalar_t__ clear_z; scalar_t__* clear_color; TYPE_2__ zs_read; TYPE_1__ color_read; } ;
struct drm_device {int dummy; } ;
struct TYPE_15__ {int paddr; int /*<<< orphan*/  base; } ;
struct TYPE_14__ {int /*<<< orphan*/  unref_head; } ;
struct TYPE_13__ {TYPE_7__ base; } ;
struct TYPE_11__ {scalar_t__ paddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (TYPE_7__*) ; 
 int PTR_ERR (TYPE_7__*) ; 
 int /*<<< orphan*/  VC4_BO_TYPE_RCL ; 
 int /*<<< orphan*/  VC4_LOADSTORE_TILE_BUFFER_NONE ; 
 scalar_t__ VC4_PACKET_BRANCH_TO_SUB_LIST_SIZE ; 
 int /*<<< orphan*/  VC4_PACKET_CLEAR_COLORS ; 
 int VC4_PACKET_CLEAR_COLORS_SIZE ; 
 scalar_t__ VC4_PACKET_LOAD_FULL_RES_TILE_BUFFER_SIZE ; 
 scalar_t__ VC4_PACKET_LOAD_TILE_BUFFER_GENERAL_SIZE ; 
 scalar_t__ VC4_PACKET_STORE_FULL_RES_TILE_BUFFER_SIZE ; 
 scalar_t__ VC4_PACKET_STORE_MS_TILE_BUFFER_SIZE ; 
 int /*<<< orphan*/  VC4_PACKET_STORE_TILE_BUFFER_GENERAL ; 
 int VC4_PACKET_STORE_TILE_BUFFER_GENERAL_SIZE ; 
 int VC4_PACKET_TILE_COORDINATES_SIZE ; 
 int /*<<< orphan*/  VC4_PACKET_TILE_RENDERING_MODE_CONFIG ; 
 int VC4_PACKET_TILE_RENDERING_MODE_CONFIG_SIZE ; 
 int VC4_PACKET_WAIT_ON_SEMAPHORE_SIZE ; 
 int VC4_SUBMIT_CL_FIXED_RCL_ORDER ; 
 int VC4_SUBMIT_CL_RCL_ORDER_INCREASING_X ; 
 int VC4_SUBMIT_CL_RCL_ORDER_INCREASING_Y ; 
 int VC4_SUBMIT_CL_USE_CLEAR_COLOR ; 
 int VC4_SUBMIT_RCL_SURFACE_READ_IS_FULL_RES ; 
 int /*<<< orphan*/  emit_tile (struct vc4_exec_info*,struct vc4_rcl_setup*,int,int,int,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcl_u16 (struct vc4_rcl_setup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcl_u32 (struct vc4_rcl_setup*,scalar_t__) ; 
 int /*<<< orphan*/  rcl_u8 (struct vc4_rcl_setup*,int /*<<< orphan*/ ) ; 
 TYPE_6__* to_vc4_bo (int /*<<< orphan*/ *) ; 
 TYPE_5__* vc4_bo_create (struct drm_device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc4_tile_coordinates (struct vc4_rcl_setup*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vc4_create_rcl_bo(struct drm_device *dev, struct vc4_exec_info *exec,
			     struct vc4_rcl_setup *setup)
{
	struct drm_vc4_submit_cl *args = exec->args;
	bool has_bin = args->bin_cl_size != 0;
	uint8_t min_x_tile = args->min_x_tile;
	uint8_t min_y_tile = args->min_y_tile;
	uint8_t max_x_tile = args->max_x_tile;
	uint8_t max_y_tile = args->max_y_tile;
	uint8_t xtiles = max_x_tile - min_x_tile + 1;
	uint8_t ytiles = max_y_tile - min_y_tile + 1;
	uint8_t xi, yi;
	uint32_t size, loop_body_size;
	bool positive_x = true;
	bool positive_y = true;

	if (args->flags & VC4_SUBMIT_CL_FIXED_RCL_ORDER) {
		if (!(args->flags & VC4_SUBMIT_CL_RCL_ORDER_INCREASING_X))
			positive_x = false;
		if (!(args->flags & VC4_SUBMIT_CL_RCL_ORDER_INCREASING_Y))
			positive_y = false;
	}

	size = VC4_PACKET_TILE_RENDERING_MODE_CONFIG_SIZE;
	loop_body_size = VC4_PACKET_TILE_COORDINATES_SIZE;

	if (args->flags & VC4_SUBMIT_CL_USE_CLEAR_COLOR) {
		size += VC4_PACKET_CLEAR_COLORS_SIZE +
			VC4_PACKET_TILE_COORDINATES_SIZE +
			VC4_PACKET_STORE_TILE_BUFFER_GENERAL_SIZE;
	}

	if (setup->color_read) {
		if (args->color_read.flags &
		    VC4_SUBMIT_RCL_SURFACE_READ_IS_FULL_RES) {
			loop_body_size += VC4_PACKET_LOAD_FULL_RES_TILE_BUFFER_SIZE;
		} else {
			loop_body_size += VC4_PACKET_LOAD_TILE_BUFFER_GENERAL_SIZE;
		}
	}
	if (setup->zs_read) {
		if (setup->color_read) {
			loop_body_size += VC4_PACKET_TILE_COORDINATES_SIZE;
			loop_body_size += VC4_PACKET_STORE_TILE_BUFFER_GENERAL_SIZE;
		}

		if (args->zs_read.flags &
		    VC4_SUBMIT_RCL_SURFACE_READ_IS_FULL_RES) {
			loop_body_size += VC4_PACKET_LOAD_FULL_RES_TILE_BUFFER_SIZE;
		} else {
			loop_body_size += VC4_PACKET_LOAD_TILE_BUFFER_GENERAL_SIZE;
		}
	}

	if (has_bin) {
		size += VC4_PACKET_WAIT_ON_SEMAPHORE_SIZE;
		loop_body_size += VC4_PACKET_BRANCH_TO_SUB_LIST_SIZE;
	}

	if (setup->msaa_color_write)
		loop_body_size += VC4_PACKET_STORE_FULL_RES_TILE_BUFFER_SIZE;
	if (setup->msaa_zs_write)
		loop_body_size += VC4_PACKET_STORE_FULL_RES_TILE_BUFFER_SIZE;

	if (setup->zs_write)
		loop_body_size += VC4_PACKET_STORE_TILE_BUFFER_GENERAL_SIZE;
	if (setup->color_write)
		loop_body_size += VC4_PACKET_STORE_MS_TILE_BUFFER_SIZE;

	/* We need a VC4_PACKET_TILE_COORDINATES in between each store. */
	loop_body_size += VC4_PACKET_TILE_COORDINATES_SIZE *
		((setup->msaa_color_write != NULL) +
		 (setup->msaa_zs_write != NULL) +
		 (setup->color_write != NULL) +
		 (setup->zs_write != NULL) - 1);

	size += xtiles * ytiles * loop_body_size;

	setup->rcl = &vc4_bo_create(dev, size, true, VC4_BO_TYPE_RCL)->base;
	if (IS_ERR(setup->rcl))
		return PTR_ERR(setup->rcl);
	list_add_tail(&to_vc4_bo(&setup->rcl->base)->unref_head,
		      &exec->unref_list);

	/* The tile buffer gets cleared when the previous tile is stored.  If
	 * the clear values changed between frames, then the tile buffer has
	 * stale clear values in it, so we have to do a store in None mode (no
	 * writes) so that we trigger the tile buffer clear.
	 */
	if (args->flags & VC4_SUBMIT_CL_USE_CLEAR_COLOR) {
		rcl_u8(setup, VC4_PACKET_CLEAR_COLORS);
		rcl_u32(setup, args->clear_color[0]);
		rcl_u32(setup, args->clear_color[1]);
		rcl_u32(setup, args->clear_z);
		rcl_u8(setup, args->clear_s);

		vc4_tile_coordinates(setup, 0, 0);

		rcl_u8(setup, VC4_PACKET_STORE_TILE_BUFFER_GENERAL);
		rcl_u16(setup, VC4_LOADSTORE_TILE_BUFFER_NONE);
		rcl_u32(setup, 0); /* no address, since we're in None mode */
	}

	rcl_u8(setup, VC4_PACKET_TILE_RENDERING_MODE_CONFIG);
	rcl_u32(setup,
		(setup->color_write ? (setup->color_write->paddr +
				       args->color_write.offset) :
		 0));
	rcl_u16(setup, args->width);
	rcl_u16(setup, args->height);
	rcl_u16(setup, args->color_write.bits);

	for (yi = 0; yi < ytiles; yi++) {
		int y = positive_y ? min_y_tile + yi : max_y_tile - yi;
		for (xi = 0; xi < xtiles; xi++) {
			int x = positive_x ? min_x_tile + xi : max_x_tile - xi;
			bool first = (xi == 0 && yi == 0);
			bool last = (xi == xtiles - 1 && yi == ytiles - 1);

			emit_tile(exec, setup, x, y, first, last);
		}
	}

	BUG_ON(setup->next_offset != size);
	exec->ct1ca = setup->rcl->paddr;
	exec->ct1ea = setup->rcl->paddr + setup->next_offset;

	return 0;
}