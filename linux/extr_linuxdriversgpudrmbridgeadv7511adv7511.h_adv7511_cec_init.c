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
struct device {int dummy; } ;
struct adv7511 {scalar_t__ type; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7511_CEC_CTRL_POWER_DOWN ; 
 scalar_t__ ADV7511_REG_CEC_CTRL ; 
 scalar_t__ ADV7533 ; 
 unsigned int ADV7533_REG_CEC_OFFSET ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int adv7511_cec_init(struct device *dev, struct adv7511 *adv7511)
{
	unsigned int offset = adv7511->type == ADV7533 ?
						ADV7533_REG_CEC_OFFSET : 0;

	regmap_write(adv7511->regmap, ADV7511_REG_CEC_CTRL + offset,
		     ADV7511_CEC_CTRL_POWER_DOWN);
	return 0;
}