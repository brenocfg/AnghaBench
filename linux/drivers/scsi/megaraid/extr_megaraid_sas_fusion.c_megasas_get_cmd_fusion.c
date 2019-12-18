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
typedef  size_t u32 ;
struct megasas_instance {struct fusion_context* ctrl_context; } ;
struct megasas_cmd_fusion {int dummy; } ;
struct fusion_context {struct megasas_cmd_fusion** cmd_list; } ;

/* Variables and functions */

inline struct megasas_cmd_fusion *megasas_get_cmd_fusion(struct megasas_instance
						  *instance, u32 blk_tag)
{
	struct fusion_context *fusion;

	fusion = instance->ctrl_context;
	return fusion->cmd_list[blk_tag];
}