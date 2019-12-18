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
struct trace_seq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num; } ;
struct mlx5_flow_destination {int type; int /*<<< orphan*/  tir_num; int /*<<< orphan*/  ft_num; int /*<<< orphan*/  ft; TYPE_1__ vport; } ;

/* Variables and functions */
#define  MLX5_FLOW_DESTINATION_TYPE_COUNTER 133 
#define  MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE 132 
#define  MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE_NUM 131 
#define  MLX5_FLOW_DESTINATION_TYPE_PORT 130 
#define  MLX5_FLOW_DESTINATION_TYPE_TIR 129 
#define  MLX5_FLOW_DESTINATION_TYPE_VPORT 128 
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,...) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 

const char *parse_fs_dst(struct trace_seq *p,
			 const struct mlx5_flow_destination *dst,
			 u32 counter_id)
{
	const char *ret = trace_seq_buffer_ptr(p);

	switch (dst->type) {
	case MLX5_FLOW_DESTINATION_TYPE_VPORT:
		trace_seq_printf(p, "vport=%u\n", dst->vport.num);
		break;
	case MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE:
		trace_seq_printf(p, "ft=%p\n", dst->ft);
		break;
	case MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE_NUM:
		trace_seq_printf(p, "ft_num=%u\n", dst->ft_num);
		break;
	case MLX5_FLOW_DESTINATION_TYPE_TIR:
		trace_seq_printf(p, "tir=%u\n", dst->tir_num);
		break;
	case MLX5_FLOW_DESTINATION_TYPE_COUNTER:
		trace_seq_printf(p, "counter_id=%u\n", counter_id);
		break;
	case MLX5_FLOW_DESTINATION_TYPE_PORT:
		trace_seq_printf(p, "port\n");
		break;
	}

	trace_seq_putc(p, 0);
	return ret;
}