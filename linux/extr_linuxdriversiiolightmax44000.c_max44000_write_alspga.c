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
struct max44000_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX44000_CFG_RX_ALSPGA_MASK ; 
 int MAX44000_CFG_RX_ALSPGA_SHIFT ; 
 int /*<<< orphan*/  MAX44000_REG_CFG_RX ; 
 int regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max44000_write_alspga(struct max44000_data *data, int val)
{
	return regmap_write_bits(data->regmap, MAX44000_REG_CFG_RX,
				 MAX44000_CFG_RX_ALSPGA_MASK,
				 val << MAX44000_CFG_RX_ALSPGA_SHIFT);
}