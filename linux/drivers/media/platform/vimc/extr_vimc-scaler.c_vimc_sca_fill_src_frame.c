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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {unsigned int height; unsigned int width; } ;
struct vimc_sca_device {TYPE_1__ sink_fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  vimc_sca_scale_pix (struct vimc_sca_device const* const,unsigned int,unsigned int,int /*<<< orphan*/  const* const) ; 

__attribute__((used)) static void vimc_sca_fill_src_frame(const struct vimc_sca_device *const vsca,
				    const u8 *const sink_frame)
{
	unsigned int i, j;

	/* Scale each pixel from the original sink frame */
	/* TODO: implement scale down, only scale up is supported for now */
	for (i = 0; i < vsca->sink_fmt.height; i++)
		for (j = 0; j < vsca->sink_fmt.width; j++)
			vimc_sca_scale_pix(vsca, i, j, sink_frame);
}