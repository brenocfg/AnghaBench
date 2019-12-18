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
struct vcap_data {int* action; int type; void** counter; } ;
struct ocelot {int dummy; } ;
struct TYPE_2__ {size_t action_words; size_t counter_words; size_t action_type_width; } ;

/* Variables and functions */
 int GENMASK (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S2_CACHE_ACTION_DAT ; 
 int /*<<< orphan*/  S2_CACHE_CNT_DAT ; 
 void* ocelot_read_rix (struct ocelot*,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__ vcap_is2 ; 

__attribute__((used)) static void vcap_cache2action(struct ocelot *oc, struct vcap_data *data)
{
	u32 i, width;

	for (i = 0; i < vcap_is2.action_words; i++)
		data->action[i] = ocelot_read_rix(oc, S2_CACHE_ACTION_DAT, i);

	for (i = 0; i < vcap_is2.counter_words; i++)
		data->counter[i] = ocelot_read_rix(oc, S2_CACHE_CNT_DAT, i);

	/* Extract action type */
	width = vcap_is2.action_type_width;
	data->type = (width ? (data->action[0] & GENMASK(width, 0)) : 0);
}