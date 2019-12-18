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
struct atmel_lcdfb_pdata {scalar_t__ lcdcon_is_backlight; scalar_t__ lcdcon_pol_negative; } ;
struct atmel_lcdfb_info {struct atmel_lcdfb_pdata pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_LCDC_CONTRAST_CTR ; 
 int /*<<< orphan*/  ATMEL_LCDC_CONTRAST_VAL ; 
 int /*<<< orphan*/  ATMEL_LCDC_CVAL_DEFAULT ; 
 int /*<<< orphan*/  ATMEL_LCDC_POL_POSITIVE ; 
 int /*<<< orphan*/  contrast_ctr ; 
 int /*<<< orphan*/  init_backlight (struct atmel_lcdfb_info*) ; 
 int /*<<< orphan*/  lcdc_writel (struct atmel_lcdfb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_contrast(struct atmel_lcdfb_info *sinfo)
{
	struct atmel_lcdfb_pdata *pdata = &sinfo->pdata;

	/* contrast pwm can be 'inverted' */
	if (pdata->lcdcon_pol_negative)
		contrast_ctr &= ~(ATMEL_LCDC_POL_POSITIVE);

	/* have some default contrast/backlight settings */
	lcdc_writel(sinfo, ATMEL_LCDC_CONTRAST_CTR, contrast_ctr);
	lcdc_writel(sinfo, ATMEL_LCDC_CONTRAST_VAL, ATMEL_LCDC_CVAL_DEFAULT);

	if (pdata->lcdcon_is_backlight)
		init_backlight(sinfo);
}