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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int MLX5E_TC_EGRESS ; 
 int /*<<< orphan*/  MLX5E_TC_FLOW_EGRESS ; 
 int /*<<< orphan*/  MLX5E_TC_FLOW_INGRESS ; 
 int MLX5E_TC_INGRESS ; 

__attribute__((used)) static void get_flags(int flags, u8 *flow_flags)
{
	u8 __flow_flags = 0;

	if (flags & MLX5E_TC_INGRESS)
		__flow_flags |= MLX5E_TC_FLOW_INGRESS;
	if (flags & MLX5E_TC_EGRESS)
		__flow_flags |= MLX5E_TC_FLOW_EGRESS;

	*flow_flags = __flow_flags;
}