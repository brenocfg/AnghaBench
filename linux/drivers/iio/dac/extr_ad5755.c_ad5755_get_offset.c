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
struct TYPE_2__ {int realbits; } ;
struct iio_chan_spec {TYPE_1__ scan_type; } ;
struct ad5755_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad5755_get_min_max (struct ad5755_state*,struct iio_chan_spec const*,int*,int*) ; 

__attribute__((used)) static inline int ad5755_get_offset(struct ad5755_state *st,
	struct iio_chan_spec const *chan)
{
	int min, max;

	ad5755_get_min_max(st, chan, &min, &max);
	return (min * (1 << chan->scan_type.realbits)) / (max - min);
}