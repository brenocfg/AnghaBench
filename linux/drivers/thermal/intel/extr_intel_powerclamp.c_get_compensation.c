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
struct TYPE_2__ {scalar_t__ confidence; int steady_comp; } ;

/* Variables and functions */
 scalar_t__ CONFIDENCE_OK ; 
 int MAX_TARGET_RATIO ; 
 TYPE_1__* cal_data ; 
 scalar_t__ reduce_irq ; 

__attribute__((used)) static unsigned int get_compensation(int ratio)
{
	unsigned int comp = 0;

	/* we only use compensation if all adjacent ones are good */
	if (ratio == 1 &&
		cal_data[ratio].confidence >= CONFIDENCE_OK &&
		cal_data[ratio + 1].confidence >= CONFIDENCE_OK &&
		cal_data[ratio + 2].confidence >= CONFIDENCE_OK) {
		comp = (cal_data[ratio].steady_comp +
			cal_data[ratio + 1].steady_comp +
			cal_data[ratio + 2].steady_comp) / 3;
	} else if (ratio == MAX_TARGET_RATIO - 1 &&
		cal_data[ratio].confidence >= CONFIDENCE_OK &&
		cal_data[ratio - 1].confidence >= CONFIDENCE_OK &&
		cal_data[ratio - 2].confidence >= CONFIDENCE_OK) {
		comp = (cal_data[ratio].steady_comp +
			cal_data[ratio - 1].steady_comp +
			cal_data[ratio - 2].steady_comp) / 3;
	} else if (cal_data[ratio].confidence >= CONFIDENCE_OK &&
		cal_data[ratio - 1].confidence >= CONFIDENCE_OK &&
		cal_data[ratio + 1].confidence >= CONFIDENCE_OK) {
		comp = (cal_data[ratio].steady_comp +
			cal_data[ratio - 1].steady_comp +
			cal_data[ratio + 1].steady_comp) / 3;
	}

	/* REVISIT: simple penalty of double idle injection */
	if (reduce_irq)
		comp = ratio;
	/* do not exceed limit */
	if (comp + ratio >= MAX_TARGET_RATIO)
		comp = MAX_TARGET_RATIO - ratio - 1;

	return comp;
}