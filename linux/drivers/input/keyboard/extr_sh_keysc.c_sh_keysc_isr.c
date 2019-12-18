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
struct sh_keysc_info {size_t mode; int* keycodes; int /*<<< orphan*/  delay; } ;
struct sh_keysc_priv {int /*<<< orphan*/  input; int /*<<< orphan*/  last_keys; struct sh_keysc_info pdata; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int keyout; int keyin; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_BITMAP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KYCR2 ; 
 int KYCR2_IRQ_DISABLED ; 
 int /*<<< orphan*/  KYINDR ; 
 int /*<<< orphan*/  KYOUTDR ; 
 int SH_KEYSC_MAXKEYS ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_complement (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_fill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_or (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keys ; 
 int /*<<< orphan*/  keys0 ; 
 int /*<<< orphan*/  keys1 ; 
 struct sh_keysc_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sh_keysc_level_mode (struct sh_keysc_priv*,unsigned char) ; 
 int /*<<< orphan*/  sh_keysc_map_dbg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* sh_keysc_mode ; 
 int sh_keysc_read (struct sh_keysc_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_keysc_write (struct sh_keysc_priv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t sh_keysc_isr(int irq, void *dev_id)
{
	struct platform_device *pdev = dev_id;
	struct sh_keysc_priv *priv = platform_get_drvdata(pdev);
	struct sh_keysc_info *pdata = &priv->pdata;
	int keyout_nr = sh_keysc_mode[pdata->mode].keyout;
	int keyin_nr = sh_keysc_mode[pdata->mode].keyin;
	DECLARE_BITMAP(keys, SH_KEYSC_MAXKEYS);
	DECLARE_BITMAP(keys0, SH_KEYSC_MAXKEYS);
	DECLARE_BITMAP(keys1, SH_KEYSC_MAXKEYS);
	unsigned char keyin_set, tmp;
	int i, k, n;

	dev_dbg(&pdev->dev, "isr!\n");

	bitmap_fill(keys1, SH_KEYSC_MAXKEYS);
	bitmap_zero(keys0, SH_KEYSC_MAXKEYS);

	do {
		bitmap_zero(keys, SH_KEYSC_MAXKEYS);
		keyin_set = 0;

		sh_keysc_write(priv, KYCR2, KYCR2_IRQ_DISABLED);

		for (i = 0; i < keyout_nr; i++) {
			n = keyin_nr * i;

			/* drive one KEYOUT pin low, read KEYIN pins */
			sh_keysc_write(priv, KYOUTDR, 0xffff ^ (3 << (i * 2)));
			udelay(pdata->delay);
			tmp = sh_keysc_read(priv, KYINDR);

			/* set bit if key press has been detected */
			for (k = 0; k < keyin_nr; k++) {
				if (tmp & (1 << k))
					__set_bit(n + k, keys);
			}

			/* keep track of which KEYIN bits that have been set */
			keyin_set |= tmp ^ ((1 << keyin_nr) - 1);
		}

		sh_keysc_level_mode(priv, keyin_set);

		bitmap_complement(keys, keys, SH_KEYSC_MAXKEYS);
		bitmap_and(keys1, keys1, keys, SH_KEYSC_MAXKEYS);
		bitmap_or(keys0, keys0, keys, SH_KEYSC_MAXKEYS);

		sh_keysc_map_dbg(&pdev->dev, keys, "keys");

	} while (sh_keysc_read(priv, KYCR2) & 0x01);

	sh_keysc_map_dbg(&pdev->dev, priv->last_keys, "last_keys");
	sh_keysc_map_dbg(&pdev->dev, keys0, "keys0");
	sh_keysc_map_dbg(&pdev->dev, keys1, "keys1");

	for (i = 0; i < SH_KEYSC_MAXKEYS; i++) {
		k = pdata->keycodes[i];
		if (!k)
			continue;

		if (test_bit(i, keys0) == test_bit(i, priv->last_keys))
			continue;

		if (test_bit(i, keys1) || test_bit(i, keys0)) {
			input_event(priv->input, EV_KEY, k, 1);
			__set_bit(i, priv->last_keys);
		}

		if (!test_bit(i, keys1)) {
			input_event(priv->input, EV_KEY, k, 0);
			__clear_bit(i, priv->last_keys);
		}

	}
	input_sync(priv->input);

	return IRQ_HANDLED;
}