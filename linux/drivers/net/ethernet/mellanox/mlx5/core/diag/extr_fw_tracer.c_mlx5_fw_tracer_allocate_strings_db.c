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
struct TYPE_2__ {int* size_out; int num_string_db; int /*<<< orphan*/ * buffer; } ;
struct mlx5_fw_tracer {TYPE_1__ str_db; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fw_tracer_free_strings_db (struct mlx5_fw_tracer*) ; 

__attribute__((used)) static int mlx5_fw_tracer_allocate_strings_db(struct mlx5_fw_tracer *tracer)
{
	u32 *string_db_size_out = tracer->str_db.size_out;
	u32 num_string_db = tracer->str_db.num_string_db;
	int i;

	for (i = 0; i < num_string_db; i++) {
		tracer->str_db.buffer[i] = kzalloc(string_db_size_out[i], GFP_KERNEL);
		if (!tracer->str_db.buffer[i])
			goto free_strings_db;
	}

	return 0;

free_strings_db:
	mlx5_fw_tracer_free_strings_db(tracer);
	return -ENOMEM;
}