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
typedef  size_t u32 ;
struct vcap_data {size_t* action; size_t type; size_t* counter; } ;
struct ocelot {int dummy; } ;
struct TYPE_2__ {size_t action_type_width; size_t action_words; size_t counter_words; } ;

/* Variables and functions */
 size_t GENMASK (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S2_CACHE_ACTION_DAT ; 
 int /*<<< orphan*/  S2_CACHE_CNT_DAT ; 
 int /*<<< orphan*/  ocelot_write_rix (struct ocelot*,size_t,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__ vcap_is2 ; 

__attribute__((used)) static void vcap_action2cache(struct ocelot *oc, struct vcap_data *data)
{
	u32 i, width, mask;

	/* Encode action type */
	width = vcap_is2.action_type_width;
	if (width) {
		mask = GENMASK(width, 0);
		data->action[0] = ((data->action[0] & ~mask) | data->type);
	}

	for (i = 0; i < vcap_is2.action_words; i++)
		ocelot_write_rix(oc, data->action[i], S2_CACHE_ACTION_DAT, i);

	for (i = 0; i < vcap_is2.counter_words; i++)
		ocelot_write_rix(oc, data->counter[i], S2_CACHE_CNT_DAT, i);
}