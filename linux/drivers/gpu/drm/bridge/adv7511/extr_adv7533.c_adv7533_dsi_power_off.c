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
struct adv7511 {int /*<<< orphan*/  regmap_cec; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int,int) ; 

void adv7533_dsi_power_off(struct adv7511 *adv)
{
	/* disable hdmi */
	regmap_write(adv->regmap_cec, 0x03, 0x0b);
	/* disable internal timing generator */
	regmap_write(adv->regmap_cec, 0x27, 0x0b);
}