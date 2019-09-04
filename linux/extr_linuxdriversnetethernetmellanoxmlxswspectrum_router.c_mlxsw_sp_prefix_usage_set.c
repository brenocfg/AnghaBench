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
struct mlxsw_sp_prefix_usage {int /*<<< orphan*/  b; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_bit (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_prefix_usage_set(struct mlxsw_sp_prefix_usage *prefix_usage,
			  unsigned char prefix_len)
{
	set_bit(prefix_len, prefix_usage->b);
}