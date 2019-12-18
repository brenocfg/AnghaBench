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
struct ina3221_data {int reg_config; int /*<<< orphan*/  pm_dev; } ;

/* Variables and functions */
 int INA3221_CONFIG_CHx_EN (int) ; 
 scalar_t__ pm_runtime_active (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool ina3221_is_enabled(struct ina3221_data *ina, int channel)
{
	return pm_runtime_active(ina->pm_dev) &&
	       (ina->reg_config & INA3221_CONFIG_CHx_EN(channel));
}