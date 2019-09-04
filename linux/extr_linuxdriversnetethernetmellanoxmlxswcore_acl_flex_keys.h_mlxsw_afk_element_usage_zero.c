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
struct mlxsw_afk_element_usage {int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_MAX ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
mlxsw_afk_element_usage_zero(struct mlxsw_afk_element_usage *elusage)
{
	bitmap_zero(elusage->usage, MLXSW_AFK_ELEMENT_MAX);
}