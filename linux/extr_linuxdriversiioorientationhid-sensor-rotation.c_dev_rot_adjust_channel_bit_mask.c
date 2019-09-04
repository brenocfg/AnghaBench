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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {char sign; int realbits; int storagebits; int repeat; } ;
struct iio_chan_spec {TYPE_1__ scan_type; } ;

/* Variables and functions */

__attribute__((used)) static void dev_rot_adjust_channel_bit_mask(struct iio_chan_spec *chan,
						int size)
{
	chan->scan_type.sign = 's';
	/* Real storage bits will change based on the report desc. */
	chan->scan_type.realbits = size * 8;
	/* Maximum size of a sample to capture is u32 */
	chan->scan_type.storagebits = sizeof(u32) * 8;
	chan->scan_type.repeat = 4;
}