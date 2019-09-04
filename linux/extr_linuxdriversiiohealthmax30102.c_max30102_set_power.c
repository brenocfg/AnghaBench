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
struct max30102_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX30102_REG_MODE_CONFIG ; 
 int /*<<< orphan*/  MAX30102_REG_MODE_CONFIG_PWR ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max30102_set_power(struct max30102_data *data, bool en)
{
	return regmap_update_bits(data->regmap, MAX30102_REG_MODE_CONFIG,
				  MAX30102_REG_MODE_CONFIG_PWR,
				  en ? 0 : MAX30102_REG_MODE_CONFIG_PWR);
}