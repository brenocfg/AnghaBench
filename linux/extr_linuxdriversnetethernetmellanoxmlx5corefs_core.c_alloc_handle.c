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
struct mlx5_flow_handle {int num_rules; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mlx5_flow_handle* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rule ; 
 int /*<<< orphan*/  struct_size (struct mlx5_flow_handle*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct mlx5_flow_handle *alloc_handle(int num_rules)
{
	struct mlx5_flow_handle *handle;

	handle = kzalloc(struct_size(handle, rule, num_rules), GFP_KERNEL);
	if (!handle)
		return NULL;

	handle->num_rules = num_rules;

	return handle;
}