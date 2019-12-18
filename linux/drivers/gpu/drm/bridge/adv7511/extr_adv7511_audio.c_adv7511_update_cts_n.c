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
struct adv7511 {int /*<<< orphan*/  regmap; int /*<<< orphan*/  f_audio; int /*<<< orphan*/  f_tmds; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7511_REG_CTS_MANUAL0 ; 
 int /*<<< orphan*/  ADV7511_REG_CTS_MANUAL1 ; 
 int /*<<< orphan*/  ADV7511_REG_CTS_MANUAL2 ; 
 int /*<<< orphan*/  ADV7511_REG_N0 ; 
 int /*<<< orphan*/  ADV7511_REG_N1 ; 
 int /*<<< orphan*/  ADV7511_REG_N2 ; 
 int /*<<< orphan*/  adv7511_calc_cts_n (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int adv7511_update_cts_n(struct adv7511 *adv7511)
{
	unsigned int cts = 0;
	unsigned int n = 0;

	adv7511_calc_cts_n(adv7511->f_tmds, adv7511->f_audio, &cts, &n);

	regmap_write(adv7511->regmap, ADV7511_REG_N0, (n >> 16) & 0xf);
	regmap_write(adv7511->regmap, ADV7511_REG_N1, (n >> 8) & 0xff);
	regmap_write(adv7511->regmap, ADV7511_REG_N2, n & 0xff);

	regmap_write(adv7511->regmap, ADV7511_REG_CTS_MANUAL0,
		     (cts >> 16) & 0xf);
	regmap_write(adv7511->regmap, ADV7511_REG_CTS_MANUAL1,
		     (cts >> 8) & 0xff);
	regmap_write(adv7511->regmap, ADV7511_REG_CTS_MANUAL2,
		     cts & 0xff);

	return 0;
}