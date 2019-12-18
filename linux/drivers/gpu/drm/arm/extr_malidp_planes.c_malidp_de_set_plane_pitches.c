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
struct TYPE_10__ {TYPE_3__* state; } ;
struct malidp_plane {TYPE_5__* layer; TYPE_6__* hwdev; TYPE_4__ base; } ;
struct TYPE_12__ {TYPE_1__* hw; } ;
struct TYPE_11__ {scalar_t__ stride_offset; scalar_t__ base; } ;
struct TYPE_9__ {TYPE_2__* fb; } ;
struct TYPE_8__ {int /*<<< orphan*/  format; } ;
struct TYPE_7__ {int features; } ;

/* Variables and functions */
 int MALIDP_DEVICE_LV_HAS_3_STRIDES ; 
 unsigned int drm_format_info_block_height (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  malidp_hw_write (TYPE_6__*,unsigned int,scalar_t__) ; 

__attribute__((used)) static void malidp_de_set_plane_pitches(struct malidp_plane *mp,
					int num_planes, unsigned int pitches[3])
{
	int i;
	int num_strides = num_planes;

	if (!mp->layer->stride_offset)
		return;

	if (num_planes == 3)
		num_strides = (mp->hwdev->hw->features &
			       MALIDP_DEVICE_LV_HAS_3_STRIDES) ? 3 : 2;

	/*
	 * The drm convention for pitch is that it needs to cover width * cpp,
	 * but our hardware wants the pitch/stride to cover all rows included
	 * in a tile.
	 */
	for (i = 0; i < num_strides; ++i) {
		unsigned int block_h = drm_format_info_block_height(mp->base.state->fb->format, i);

		malidp_hw_write(mp->hwdev, pitches[i] * block_h,
				mp->layer->base +
				mp->layer->stride_offset + i * 4);
	}
}