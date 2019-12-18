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
struct TYPE_3__ {int /*<<< orphan*/  top_freq; int /*<<< orphan*/  bot_freq; } ;
struct TYPE_4__ {TYPE_1__ region; } ;
struct fmdev {TYPE_2__ rx; } ;

/* Variables and functions */

int fm_rx_get_band_freq_range(struct fmdev *fmdev, u32 *bot_freq, u32 *top_freq)
{
	if (bot_freq != NULL)
		*bot_freq = fmdev->rx.region.bot_freq;

	if (top_freq != NULL)
		*top_freq = fmdev->rx.region.top_freq;

	return 0;
}