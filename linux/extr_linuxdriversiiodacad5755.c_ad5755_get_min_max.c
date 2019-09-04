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
struct iio_chan_spec {size_t channel; } ;
struct ad5755_state {int* ctrl; } ;
typedef  enum ad5755_mode { ____Placeholder_ad5755_mode } ad5755_mode ;

/* Variables and functions */
 int** ad5755_min_max_table ; 

__attribute__((used)) static void ad5755_get_min_max(struct ad5755_state *st,
	struct iio_chan_spec const *chan, int *min, int *max)
{
	enum ad5755_mode mode = st->ctrl[chan->channel] & 7;
	*min = ad5755_min_max_table[mode][0];
	*max = ad5755_min_max_table[mode][1];
}