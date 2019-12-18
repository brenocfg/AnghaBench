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
struct max77693_dev {struct regmap* regmap; struct regmap* regmap_chg; } ;
typedef  enum max77693_types { ____Placeholder_max77693_types } max77693_types ;

/* Variables and functions */
#define  MAX77843_CHARGER 130 
#define  MAX77843_SAFEOUT1 129 
#define  MAX77843_SAFEOUT2 128 
 int TYPE_MAX77693 ; 

__attribute__((used)) static struct regmap *max77693_get_regmap(enum max77693_types type,
					  struct max77693_dev *max77693,
					  int reg_id)
{
	if (type == TYPE_MAX77693)
		return max77693->regmap;

	/* Else: TYPE_MAX77843 */
	switch (reg_id) {
	case MAX77843_SAFEOUT1:
	case MAX77843_SAFEOUT2:
		return max77693->regmap;
	case MAX77843_CHARGER:
		return max77693->regmap_chg;
	default:
		return max77693->regmap;
	}
}