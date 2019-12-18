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
struct tracer_string_format {int /*<<< orphan*/  hlist; } ;
struct TYPE_2__ {int /*<<< orphan*/  tmsn; } ;
struct tracer_event {TYPE_1__ string_event; } ;
struct mlx5_fw_tracer {struct hlist_head* hash; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 struct tracer_string_format* kzalloc (int,int /*<<< orphan*/ ) ; 
 size_t mlx5_tracer_message_hash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tracer_string_format *mlx5_tracer_message_insert(struct mlx5_fw_tracer *tracer,
							       struct tracer_event *tracer_event)
{
	struct hlist_head *head =
		&tracer->hash[mlx5_tracer_message_hash(tracer_event->string_event.tmsn)];
	struct tracer_string_format *cur_string;

	cur_string = kzalloc(sizeof(*cur_string), GFP_KERNEL);
	if (!cur_string)
		return NULL;

	hlist_add_head(&cur_string->hlist, head);

	return cur_string;
}