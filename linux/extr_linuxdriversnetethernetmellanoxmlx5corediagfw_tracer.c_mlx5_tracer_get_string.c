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
typedef  scalar_t__ u32 ;
struct tracer_string_format {char* string; } ;
struct TYPE_3__ {scalar_t__ string_param; } ;
struct tracer_event {TYPE_1__ string_event; } ;
struct TYPE_4__ {int num_string_db; scalar_t__* base_address_out; scalar_t__* size_out; scalar_t__* buffer; } ;
struct mlx5_fw_tracer {TYPE_2__ str_db; } ;

/* Variables and functions */
 struct tracer_string_format* mlx5_tracer_message_insert (struct mlx5_fw_tracer*,struct tracer_event*) ; 

__attribute__((used)) static struct tracer_string_format *mlx5_tracer_get_string(struct mlx5_fw_tracer *tracer,
							   struct tracer_event *tracer_event)
{
	struct tracer_string_format *cur_string;
	u32 str_ptr, offset;
	int i;

	str_ptr = tracer_event->string_event.string_param;

	for (i = 0; i < tracer->str_db.num_string_db; i++) {
		if (str_ptr > tracer->str_db.base_address_out[i] &&
		    str_ptr < tracer->str_db.base_address_out[i] +
		    tracer->str_db.size_out[i]) {
			offset = str_ptr - tracer->str_db.base_address_out[i];
			/* add it to the hash */
			cur_string = mlx5_tracer_message_insert(tracer, tracer_event);
			if (!cur_string)
				return NULL;
			cur_string->string = (char *)(tracer->str_db.buffer[i] +
							offset);
			return cur_string;
		}
	}

	return NULL;
}