#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct ssd1307fb_par {int pwm_period; int contrast; int com_invdir; int height; int com_offset; int dclk_div; int dclk_frq; int prechargep1; int prechargep2; int com_lrremap; int vcomh; int* lookup_table; int width; int page_offset; TYPE_2__* client; scalar_t__ lookup_table_set; TYPE_1__* device_info; int /*<<< orphan*/  com_seq; scalar_t__ low_power; scalar_t__ area_color_enable; scalar_t__ seg_remap; TYPE_3__* pwm; } ;
struct pwm_args {int period; } ;
struct TYPE_12__ {int /*<<< orphan*/  pwm; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {scalar_t__ need_chargepump; scalar_t__ need_pwm; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int BIT (int) ; 
 int DIV_ROUND_UP (int,int) ; 
 scalar_t__ IS_ERR (TYPE_3__*) ; 
 int PTR_ERR (TYPE_3__*) ; 
 int SSD1307FB_CHARGE_PUMP ; 
 int SSD1307FB_CONTRAST ; 
 int SSD1307FB_DISPLAY_ON ; 
 int SSD1307FB_SEG_REMAP_ON ; 
 int SSD1307FB_SET_ADDRESS_MODE ; 
 int SSD1307FB_SET_ADDRESS_MODE_HORIZONTAL ; 
 int SSD1307FB_SET_AREA_COLOR_MODE ; 
 int SSD1307FB_SET_CLOCK_FREQ ; 
 int SSD1307FB_SET_COL_RANGE ; 
 int SSD1307FB_SET_COM_PINS_CONFIG ; 
 int SSD1307FB_SET_DISPLAY_OFFSET ; 
 int SSD1307FB_SET_LOOKUP_TABLE ; 
 int SSD1307FB_SET_MULTIPLEX_RATIO ; 
 int SSD1307FB_SET_PAGE_RANGE ; 
 int SSD1307FB_SET_PRECHARGE_PERIOD ; 
 int SSD1307FB_SET_VCOMH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  pwm_apply_args (TYPE_3__*) ; 
 int /*<<< orphan*/  pwm_config (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  pwm_enable (TYPE_3__*) ; 
 TYPE_3__* pwm_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwm_get_args (TYPE_3__*,struct pwm_args*) ; 
 int /*<<< orphan*/  ssd1307fb_update_display (struct ssd1307fb_par*) ; 
 int ssd1307fb_write_cmd (TYPE_2__*,int) ; 

__attribute__((used)) static int ssd1307fb_init(struct ssd1307fb_par *par)
{
	int ret;
	u32 precharge, dclk, com_invdir, compins;
	struct pwm_args pargs;

	if (par->device_info->need_pwm) {
		par->pwm = pwm_get(&par->client->dev, NULL);
		if (IS_ERR(par->pwm)) {
			dev_err(&par->client->dev, "Could not get PWM from device tree!\n");
			return PTR_ERR(par->pwm);
		}

		/*
		 * FIXME: pwm_apply_args() should be removed when switching to
		 * the atomic PWM API.
		 */
		pwm_apply_args(par->pwm);

		pwm_get_args(par->pwm, &pargs);

		par->pwm_period = pargs.period;
		/* Enable the PWM */
		pwm_config(par->pwm, par->pwm_period / 2, par->pwm_period);
		pwm_enable(par->pwm);

		dev_dbg(&par->client->dev, "Using PWM%d with a %dns period.\n",
			par->pwm->pwm, par->pwm_period);
	}

	/* Set initial contrast */
	ret = ssd1307fb_write_cmd(par->client, SSD1307FB_CONTRAST);
	if (ret < 0)
		return ret;

	ret = ssd1307fb_write_cmd(par->client, par->contrast);
	if (ret < 0)
		return ret;

	/* Set segment re-map */
	if (par->seg_remap) {
		ret = ssd1307fb_write_cmd(par->client, SSD1307FB_SEG_REMAP_ON);
		if (ret < 0)
			return ret;
	}

	/* Set COM direction */
	com_invdir = 0xc0 | par->com_invdir << 3;
	ret = ssd1307fb_write_cmd(par->client,  com_invdir);
	if (ret < 0)
		return ret;

	/* Set multiplex ratio value */
	ret = ssd1307fb_write_cmd(par->client, SSD1307FB_SET_MULTIPLEX_RATIO);
	if (ret < 0)
		return ret;

	ret = ssd1307fb_write_cmd(par->client, par->height - 1);
	if (ret < 0)
		return ret;

	/* set display offset value */
	ret = ssd1307fb_write_cmd(par->client, SSD1307FB_SET_DISPLAY_OFFSET);
	if (ret < 0)
		return ret;

	ret = ssd1307fb_write_cmd(par->client, par->com_offset);
	if (ret < 0)
		return ret;

	/* Set clock frequency */
	ret = ssd1307fb_write_cmd(par->client, SSD1307FB_SET_CLOCK_FREQ);
	if (ret < 0)
		return ret;

	dclk = ((par->dclk_div - 1) & 0xf) | (par->dclk_frq & 0xf) << 4;
	ret = ssd1307fb_write_cmd(par->client, dclk);
	if (ret < 0)
		return ret;

	/* Set Set Area Color Mode ON/OFF & Low Power Display Mode */
	if (par->area_color_enable || par->low_power) {
		u32 mode;

		ret = ssd1307fb_write_cmd(par->client,
					  SSD1307FB_SET_AREA_COLOR_MODE);
		if (ret < 0)
			return ret;

		mode = (par->area_color_enable ? 0x30 : 0) |
			(par->low_power ? 5 : 0);
		ret = ssd1307fb_write_cmd(par->client, mode);
		if (ret < 0)
			return ret;
	}

	/* Set precharge period in number of ticks from the internal clock */
	ret = ssd1307fb_write_cmd(par->client, SSD1307FB_SET_PRECHARGE_PERIOD);
	if (ret < 0)
		return ret;

	precharge = (par->prechargep1 & 0xf) | (par->prechargep2 & 0xf) << 4;
	ret = ssd1307fb_write_cmd(par->client, precharge);
	if (ret < 0)
		return ret;

	/* Set COM pins configuration */
	ret = ssd1307fb_write_cmd(par->client, SSD1307FB_SET_COM_PINS_CONFIG);
	if (ret < 0)
		return ret;

	compins = 0x02 | !par->com_seq << 4 | par->com_lrremap << 5;
	ret = ssd1307fb_write_cmd(par->client, compins);
	if (ret < 0)
		return ret;

	/* Set VCOMH */
	ret = ssd1307fb_write_cmd(par->client, SSD1307FB_SET_VCOMH);
	if (ret < 0)
		return ret;

	ret = ssd1307fb_write_cmd(par->client, par->vcomh);
	if (ret < 0)
		return ret;

	/* Turn on the DC-DC Charge Pump */
	ret = ssd1307fb_write_cmd(par->client, SSD1307FB_CHARGE_PUMP);
	if (ret < 0)
		return ret;

	ret = ssd1307fb_write_cmd(par->client,
		BIT(4) | (par->device_info->need_chargepump ? BIT(2) : 0));
	if (ret < 0)
		return ret;

	/* Set lookup table */
	if (par->lookup_table_set) {
		int i;

		ret = ssd1307fb_write_cmd(par->client,
					  SSD1307FB_SET_LOOKUP_TABLE);
		if (ret < 0)
			return ret;

		for (i = 0; i < ARRAY_SIZE(par->lookup_table); ++i) {
			u8 val = par->lookup_table[i];

			if (val < 31 || val > 63)
				dev_warn(&par->client->dev,
					 "lookup table index %d value out of range 31 <= %d <= 63\n",
					 i, val);
			ret = ssd1307fb_write_cmd(par->client, val);
			if (ret < 0)
				return ret;
		}
	}

	/* Switch to horizontal addressing mode */
	ret = ssd1307fb_write_cmd(par->client, SSD1307FB_SET_ADDRESS_MODE);
	if (ret < 0)
		return ret;

	ret = ssd1307fb_write_cmd(par->client,
				  SSD1307FB_SET_ADDRESS_MODE_HORIZONTAL);
	if (ret < 0)
		return ret;

	/* Set column range */
	ret = ssd1307fb_write_cmd(par->client, SSD1307FB_SET_COL_RANGE);
	if (ret < 0)
		return ret;

	ret = ssd1307fb_write_cmd(par->client, 0x0);
	if (ret < 0)
		return ret;

	ret = ssd1307fb_write_cmd(par->client, par->width - 1);
	if (ret < 0)
		return ret;

	/* Set page range */
	ret = ssd1307fb_write_cmd(par->client, SSD1307FB_SET_PAGE_RANGE);
	if (ret < 0)
		return ret;

	ret = ssd1307fb_write_cmd(par->client, par->page_offset);
	if (ret < 0)
		return ret;

	ret = ssd1307fb_write_cmd(par->client,
				  par->page_offset +
				  DIV_ROUND_UP(par->height, 8) - 1);
	if (ret < 0)
		return ret;

	/* Clear the screen */
	ssd1307fb_update_display(par);

	/* Turn on the display */
	ret = ssd1307fb_write_cmd(par->client, SSD1307FB_DISPLAY_ON);
	if (ret < 0)
		return ret;

	return 0;
}