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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ MLX5E_MAX_PTYS_LEGACY_SPEED ; 

__attribute__((used)) static bool ext_speed_requested(u32 speed)
{
#define MLX5E_MAX_PTYS_LEGACY_SPEED 100000
	return !!(speed > MLX5E_MAX_PTYS_LEGACY_SPEED);
}