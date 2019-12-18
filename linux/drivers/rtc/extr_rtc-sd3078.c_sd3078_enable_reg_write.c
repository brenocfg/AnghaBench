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
struct sd3078 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_WRITE1 ; 
 int /*<<< orphan*/  KEY_WRITE2 ; 
 int /*<<< orphan*/  KEY_WRITE3 ; 
 int /*<<< orphan*/  SD3078_REG_CTRL1 ; 
 int /*<<< orphan*/  SD3078_REG_CTRL2 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd3078_enable_reg_write(struct sd3078 *sd3078)
{
	regmap_update_bits(sd3078->regmap, SD3078_REG_CTRL2,
			   KEY_WRITE1, KEY_WRITE1);
	regmap_update_bits(sd3078->regmap, SD3078_REG_CTRL1,
			   KEY_WRITE2, KEY_WRITE2);
	regmap_update_bits(sd3078->regmap, SD3078_REG_CTRL1,
			   KEY_WRITE3, KEY_WRITE3);
}