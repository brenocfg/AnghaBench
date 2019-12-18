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
struct max17042_chip {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX17042_MLOCKReg1 ; 
 int /*<<< orphan*/  MAX17042_MLOCKReg2 ; 
 int /*<<< orphan*/  MODEL_UNLOCK1 ; 
 int /*<<< orphan*/  MODEL_UNLOCK2 ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void max17042_unlock_model(struct max17042_chip *chip)
{
	struct regmap *map = chip->regmap;

	regmap_write(map, MAX17042_MLOCKReg1, MODEL_UNLOCK1);
	regmap_write(map, MAX17042_MLOCKReg2, MODEL_UNLOCK2);
}