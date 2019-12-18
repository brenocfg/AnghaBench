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

/* Variables and functions */
 unsigned long BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EGRESS ; 
 int /*<<< orphan*/  ESW_OFFLOAD ; 
 int /*<<< orphan*/  INGRESS ; 
 int /*<<< orphan*/  MLX5E_TC_FLOW_FLAG_EGRESS ; 
 int /*<<< orphan*/  MLX5E_TC_FLOW_FLAG_ESWITCH ; 
 int /*<<< orphan*/  MLX5E_TC_FLOW_FLAG_INGRESS ; 
 int /*<<< orphan*/  MLX5E_TC_FLOW_FLAG_NIC ; 
 int MLX5_TC_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIC_OFFLOAD ; 

__attribute__((used)) static void get_flags(int flags, unsigned long *flow_flags)
{
	unsigned long __flow_flags = 0;

	if (flags & MLX5_TC_FLAG(INGRESS))
		__flow_flags |= BIT(MLX5E_TC_FLOW_FLAG_INGRESS);
	if (flags & MLX5_TC_FLAG(EGRESS))
		__flow_flags |= BIT(MLX5E_TC_FLOW_FLAG_EGRESS);

	if (flags & MLX5_TC_FLAG(ESW_OFFLOAD))
		__flow_flags |= BIT(MLX5E_TC_FLOW_FLAG_ESWITCH);
	if (flags & MLX5_TC_FLAG(NIC_OFFLOAD))
		__flow_flags |= BIT(MLX5E_TC_FLOW_FLAG_NIC);

	*flow_flags = __flow_flags;
}