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
struct lp3952_led_array {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  CET197 ; 
 int /*<<< orphan*/  I100 ; 
 int /*<<< orphan*/  I46 ; 
 int /*<<< orphan*/  I71 ; 
 int LP3952_ACTIVE_MODE ; 
 int LP3952_INT_B00ST_LDR ; 
 int LP3952_PATRN_GEN_EN ; 
 int LP3952_PATRN_LOOP ; 
 int /*<<< orphan*/  LP3952_REG_ENABLES ; 
 int /*<<< orphan*/  LP3952_REG_LED_CTRL ; 
 int /*<<< orphan*/  LP3952_REG_PAT_GEN_CTRL ; 
 int /*<<< orphan*/  TT0 ; 
 int lp3952_register_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int lp3952_set_pattern_gen_cmd (struct lp3952_led_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp3952_configure(struct lp3952_led_array *priv)
{
	int ret;

	/* Disable any LEDs on from any previous conf. */
	ret = lp3952_register_write(priv->client, LP3952_REG_LED_CTRL, 0);
	if (ret)
		return ret;

	/* enable rgb patter, loop */
	ret = lp3952_register_write(priv->client, LP3952_REG_PAT_GEN_CTRL,
				    LP3952_PATRN_LOOP | LP3952_PATRN_GEN_EN);
	if (ret)
		return ret;

	/* Update Bit 6 (Active mode), Select both Led sets, Bit [1:0] */
	ret = lp3952_register_write(priv->client, LP3952_REG_ENABLES,
				    LP3952_ACTIVE_MODE | LP3952_INT_B00ST_LDR);
	if (ret)
		return ret;

	/* Set Cmd1 for RGB intensity,cmd and transition time */
	return lp3952_set_pattern_gen_cmd(priv, 0, I46, I71, I100, TT0,
					   CET197);
}