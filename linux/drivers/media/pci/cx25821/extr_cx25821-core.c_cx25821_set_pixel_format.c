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
typedef  int /*<<< orphan*/  u32 ;
struct cx25821_dev {TYPE_2__* channels; } ;
struct TYPE_4__ {int /*<<< orphan*/  pixel_formats; TYPE_1__* sram_channels; } ;
struct TYPE_3__ {int /*<<< orphan*/  pix_frmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cx25821_set_pixel_format(struct cx25821_dev *dev, int channel_select,
			      u32 format)
{
	if (channel_select <= 7 && channel_select >= 0) {
		cx_write(dev->channels[channel_select].sram_channels->pix_frmt,
				format);
	}
	dev->channels[channel_select].pixel_formats = format;
}