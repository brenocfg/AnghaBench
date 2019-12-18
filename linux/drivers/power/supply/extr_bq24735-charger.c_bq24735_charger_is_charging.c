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
struct bq24735 {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ24735_CHG_OPT ; 
 int BQ24735_CHG_OPT_CHARGE_DISABLE ; 
 int /*<<< orphan*/  bq24735_charger_is_present (struct bq24735*) ; 
 int bq24735_read_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bq24735_charger_is_charging(struct bq24735 *charger)
{
	int ret;

	if (!bq24735_charger_is_present(charger))
		return 0;

	ret  = bq24735_read_word(charger->client, BQ24735_CHG_OPT);
	if (ret < 0)
		return ret;

	return !(ret & BQ24735_CHG_OPT_CHARGE_DISABLE);
}