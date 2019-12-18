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
struct qt1050_priv {struct qt1050_key* keys; struct regmap* regmap; } ;
struct qt1050_key_regs {int /*<<< orphan*/  nthr; int /*<<< orphan*/  csd; int /*<<< orphan*/  pulse_scale; } ;
struct qt1050_key {scalar_t__ keycode; int num; int samples; int scale; int charge_delay; int thr_cnt; } ;

/* Variables and functions */
 scalar_t__ KEY_RESERVED ; 
 int QT1050_MAX_KEYS ; 
 struct qt1050_key_regs* qt1050_get_key_regs (int) ; 
 int qt1050_set_key (struct regmap*,int,int) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qt1050_apply_fw_data(struct qt1050_priv *ts)
{
	struct regmap *map = ts->regmap;
	struct qt1050_key *button = &ts->keys[0];
	const struct qt1050_key_regs *key_regs;
	int i, err;

	/* Disable all keys and enable only the specified ones */
	for (i = 0; i < QT1050_MAX_KEYS; i++) {
		err = qt1050_set_key(map, i, 0);
		if (err)
			return err;
	}

	for (i = 0; i < QT1050_MAX_KEYS; i++, button++) {
		/* Keep KEY_RESERVED keys off */
		if (button->keycode == KEY_RESERVED)
			continue;

		err = qt1050_set_key(map, button->num, 1);
		if (err)
			return err;

		key_regs = qt1050_get_key_regs(button->num);

		err = regmap_write(map, key_regs->pulse_scale,
				   (button->samples << 4) | (button->scale));
		if (err)
			return err;
		err = regmap_write(map, key_regs->csd, button->charge_delay);
		if (err)
			return err;
		err = regmap_write(map, key_regs->nthr, button->thr_cnt);
		if (err)
			return err;
	}

	return 0;
}