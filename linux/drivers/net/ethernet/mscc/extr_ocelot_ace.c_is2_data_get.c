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
typedef  int u32 ;
struct vcap_data {int tg_sw; int tg_value; int key_offset; int counter_offset; int type; scalar_t__ action_offset; int /*<<< orphan*/  tg_mask; } ;
struct TYPE_4__ {int tg_width; int sw_count; int entry_width; int counter_width; scalar_t__ action_type_width; TYPE_1__* action_table; } ;
struct TYPE_3__ {int width; int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENMASK (int,int) ; 
 int VCAP_TG_HALF ; 
 TYPE_2__ vcap_is2 ; 

__attribute__((used)) static void is2_data_get(struct vcap_data *data, int ix)
{
	u32 i, col, offset, count, cnt, base, width = vcap_is2.tg_width;

	count = (data->tg_sw == VCAP_TG_HALF ? 2 : 4);
	col = (ix % 2);
	cnt = (vcap_is2.sw_count / count);
	base = (vcap_is2.sw_count - col * cnt - cnt);
	data->tg_value = 0;
	data->tg_mask = 0;
	for (i = 0; i < cnt; i++) {
		offset = ((base + i) * width);
		data->tg_value |= (data->tg_sw << offset);
		data->tg_mask |= GENMASK(offset + width - 1, offset);
	}

	/* Calculate key/action/counter offsets */
	col = (count - col - 1);
	data->key_offset = (base * vcap_is2.entry_width) / vcap_is2.sw_count;
	data->counter_offset = (cnt * col * vcap_is2.counter_width);
	i = data->type;
	width = vcap_is2.action_table[i].width;
	cnt = vcap_is2.action_table[i].count;
	data->action_offset =
		(((cnt * col * width) / count) + vcap_is2.action_type_width);
}