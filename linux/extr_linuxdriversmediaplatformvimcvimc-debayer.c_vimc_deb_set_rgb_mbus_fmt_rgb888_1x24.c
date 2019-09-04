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
struct TYPE_2__ {int /*<<< orphan*/  width; } ;
struct vimc_deb_device {unsigned int* src_frame; TYPE_1__ sink_fmt; } ;

/* Variables and functions */
 unsigned int VIMC_FRAME_INDEX (unsigned int,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vimc_deb_set_rgb_mbus_fmt_rgb888_1x24(struct vimc_deb_device *vdeb,
						  unsigned int lin,
						  unsigned int col,
						  unsigned int rgb[3])
{
	unsigned int i, index;

	index = VIMC_FRAME_INDEX(lin, col, vdeb->sink_fmt.width, 3);
	for (i = 0; i < 3; i++)
		vdeb->src_frame[index + i] = rgb[i];
}