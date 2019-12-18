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
struct pattern_trig_data {size_t npatterns; TYPE_1__* patterns; } ;
struct TYPE_2__ {int /*<<< orphan*/  delta_t; int /*<<< orphan*/  brightness; } ;

/* Variables and functions */

__attribute__((used)) static int pattern_trig_store_patterns_int(struct pattern_trig_data *data,
					   const u32 *buf, size_t count)
{
	unsigned int i;

	for (i = 0; i < count; i += 2) {
		data->patterns[data->npatterns].brightness = buf[i];
		data->patterns[data->npatterns].delta_t = buf[i + 1];
		data->npatterns++;
	}

	return 0;
}