#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct mn88443x_priv {TYPE_1__* spec; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  mclk; struct regmap* regmap_t; } ;
struct TYPE_2__ {scalar_t__ primary; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIZSET1 ; 
 int /*<<< orphan*/  HIZSET2 ; 
 int /*<<< orphan*/  HIZSET3 ; 
 int /*<<< orphan*/  OUTCSET ; 
 int OUTCSET_CHDRV_8MA ; 
 int /*<<< orphan*/  PLDWSET ; 
 int PLDWSET_NORMAL ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void mn88443x_cmn_power_on(struct mn88443x_priv *chip)
{
	struct regmap *r_t = chip->regmap_t;

	clk_prepare_enable(chip->mclk);

	gpiod_set_value_cansleep(chip->reset_gpio, 1);
	usleep_range(100, 1000);
	gpiod_set_value_cansleep(chip->reset_gpio, 0);

	if (chip->spec->primary) {
		regmap_write(r_t, OUTCSET, OUTCSET_CHDRV_8MA);
		regmap_write(r_t, PLDWSET, PLDWSET_NORMAL);
		regmap_write(r_t, HIZSET1, 0x80);
		regmap_write(r_t, HIZSET2, 0xe0);
	} else {
		regmap_write(r_t, HIZSET3, 0x8f);
	}
}