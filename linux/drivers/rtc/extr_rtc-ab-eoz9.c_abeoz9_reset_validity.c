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
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABEOZ9_REG_CTRL_STATUS ; 
 int ABEOZ9_REG_CTRL_STATUS_PON ; 
 int ABEOZ9_REG_CTRL_STATUS_V1F ; 
 int ABEOZ9_REG_CTRL_STATUS_V2F ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int abeoz9_reset_validity(struct regmap *regmap)
{
	return regmap_update_bits(regmap, ABEOZ9_REG_CTRL_STATUS,
				  ABEOZ9_REG_CTRL_STATUS_V1F |
				  ABEOZ9_REG_CTRL_STATUS_V2F |
				  ABEOZ9_REG_CTRL_STATUS_PON,
				  0);
}