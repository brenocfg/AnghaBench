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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ MLX5_ACTION_IN_FIELD_OUT_IP_TTL ; 
 scalar_t__ MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  field ; 
 int /*<<< orphan*/  set_action_in ; 

__attribute__((used)) static bool
dr_action_modify_check_is_ttl_modify(const u64 *sw_action)
{
	u16 sw_field = MLX5_GET(set_action_in, sw_action, field);

	return sw_field == MLX5_ACTION_IN_FIELD_OUT_IP_TTL;
}