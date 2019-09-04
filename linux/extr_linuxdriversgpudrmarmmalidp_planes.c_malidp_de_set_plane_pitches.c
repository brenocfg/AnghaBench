#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct malidp_plane {TYPE_1__* layer; TYPE_3__* hwdev; } ;
struct TYPE_6__ {TYPE_2__* hw; } ;
struct TYPE_5__ {int features; } ;
struct TYPE_4__ {scalar_t__ stride_offset; scalar_t__ base; } ;

/* Variables and functions */
 int MALIDP_DEVICE_LV_HAS_3_STRIDES ; 
 int /*<<< orphan*/  malidp_hw_write (TYPE_3__*,unsigned int,scalar_t__) ; 

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

	for (i = 0; i < num_strides; ++i)
		malidp_hw_write(mp->hwdev, pitches[i],
				mp->layer->base +
				mp->layer->stride_offset + i * 4);
}