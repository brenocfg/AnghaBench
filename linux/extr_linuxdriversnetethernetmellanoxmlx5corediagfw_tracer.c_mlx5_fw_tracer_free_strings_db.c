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
typedef  int u32 ;
struct TYPE_2__ {int num_string_db; int /*<<< orphan*/ ** buffer; } ;
struct mlx5_fw_tracer {TYPE_1__ str_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5_fw_tracer_free_strings_db(struct mlx5_fw_tracer *tracer)
{
	u32 num_string_db = tracer->str_db.num_string_db;
	int i;

	for (i = 0; i < num_string_db; i++) {
		kfree(tracer->str_db.buffer[i]);
		tracer->str_db.buffer[i] = NULL;
	}
}