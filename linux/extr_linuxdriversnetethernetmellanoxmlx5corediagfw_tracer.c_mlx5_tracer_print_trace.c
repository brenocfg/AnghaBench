#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  tmp ;
struct tracer_string_format {char* string; int /*<<< orphan*/  event_id; int /*<<< orphan*/  lost; int /*<<< orphan*/ * params; } ;
struct mlx5_core_dev {int /*<<< orphan*/  tracer; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_tracer_clean_message (struct tracer_string_format*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_mlx5_fw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void mlx5_tracer_print_trace(struct tracer_string_format *str_frmt,
				    struct mlx5_core_dev *dev,
				    u64 trace_timestamp)
{
	char	tmp[512];

	snprintf(tmp, sizeof(tmp), str_frmt->string,
		 str_frmt->params[0],
		 str_frmt->params[1],
		 str_frmt->params[2],
		 str_frmt->params[3],
		 str_frmt->params[4],
		 str_frmt->params[5],
		 str_frmt->params[6]);

	trace_mlx5_fw(dev->tracer, trace_timestamp, str_frmt->lost,
		      str_frmt->event_id, tmp);

	/* remove it from hash */
	mlx5_tracer_clean_message(str_frmt);
}