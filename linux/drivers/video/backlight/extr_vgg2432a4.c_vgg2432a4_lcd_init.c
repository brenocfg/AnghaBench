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
struct ili9320_platdata {int display2; int display3; int display4; int rgb_if1; int rgb_if2; int hsize; int vsize; int interface2; int interface3; int interface4; int interface5; int interface6; } ;
struct ili9320 {int display1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int ILI9320_BASE_IMAGE ; 
 unsigned int ILI9320_DISPLAY1 ; 
 int ILI9320_DISPLAY1_BASEE ; 
 int ILI9320_DISPLAY1_D (int) ; 
 int ILI9320_DISPLAY1_DTE ; 
 int ILI9320_DISPLAY1_GON ; 
 unsigned int ILI9320_DISPLAY2 ; 
 unsigned int ILI9320_DISPLAY3 ; 
 unsigned int ILI9320_DISPLAY4 ; 
 unsigned int ILI9320_DRIVER2 ; 
 int ILI9320_DRIVER2_NL (int) ; 
 unsigned int ILI9320_FRAMEMAKER ; 
 unsigned int ILI9320_GRAM_HORIZ_ADDR ; 
 unsigned int ILI9320_GRAM_VERT_ADD ; 
 unsigned int ILI9320_HORIZ_END ; 
 unsigned int ILI9320_HORIZ_START ; 
 unsigned int ILI9320_INTERFACE1 ; 
 unsigned int ILI9320_INTERFACE2 ; 
 unsigned int ILI9320_INTERFACE3 ; 
 unsigned int ILI9320_INTERFACE4 ; 
 unsigned int ILI9320_INTERFACE5 ; 
 unsigned int ILI9320_INTERFACE6 ; 
 unsigned int ILI9320_OSCILATION ; 
 int ILI9320_OSCILATION_OSC ; 
 unsigned int ILI9320_PARTIAL1_POSITION ; 
 unsigned int ILI9320_PARTIAL2_END ; 
 unsigned int ILI9320_POWER3 ; 
 unsigned int ILI9320_POWER4 ; 
 unsigned int ILI9320_POWER7 ; 
 unsigned int ILI9320_RGB_IF1 ; 
 unsigned int ILI9320_RGB_IF2 ; 
 unsigned int ILI9320_VERT_END ; 
 unsigned int ILI9320_VERT_SCROLL ; 
 unsigned int ILI9320_VERT_START ; 
 int ili9320_write (struct ili9320*,unsigned int,int) ; 
 int ili9320_write_regs (struct ili9320*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  vgg_gamma ; 
 int /*<<< orphan*/  vgg_init0 ; 
 int /*<<< orphan*/  vgg_init1 ; 
 int /*<<< orphan*/  vgg_init2 ; 

__attribute__((used)) static int vgg2432a4_lcd_init(struct ili9320 *lcd,
			      struct ili9320_platdata *cfg)
{
	unsigned int addr;
	int ret;

	/* Set VCore before anything else (VGG243237-6UFLWA) */
	ret = ili9320_write(lcd, 0x00e5, 0x8000);
	if (ret)
		goto err_initial;

	/* Start the oscillator up before we can do anything else. */
	ret = ili9320_write(lcd, ILI9320_OSCILATION, ILI9320_OSCILATION_OSC);
	if (ret)
		goto err_initial;

	/* must wait at-lesat 10ms after starting */
	mdelay(15);

	ret = ili9320_write_regs(lcd, vgg_init0, ARRAY_SIZE(vgg_init0));
	if (ret != 0)
		goto err_initial;

	ili9320_write(lcd, ILI9320_DISPLAY2, cfg->display2);
	ili9320_write(lcd, ILI9320_DISPLAY3, cfg->display3);
	ili9320_write(lcd, ILI9320_DISPLAY4, cfg->display4);

	ili9320_write(lcd, ILI9320_RGB_IF1, cfg->rgb_if1);
	ili9320_write(lcd, ILI9320_FRAMEMAKER, 0x0);
	ili9320_write(lcd, ILI9320_RGB_IF2, cfg->rgb_if2);

	ret = ili9320_write_regs(lcd, vgg_init1, ARRAY_SIZE(vgg_init1));
	if (ret != 0)
		goto err_vgg;

	mdelay(300);

	ret = ili9320_write_regs(lcd, vgg_init2, ARRAY_SIZE(vgg_init2));
	if (ret != 0)
		goto err_vgg2;

	mdelay(100);

	ili9320_write(lcd, ILI9320_POWER3, 0x13c);

	mdelay(100);

	ili9320_write(lcd, ILI9320_POWER4, 0x1c00);
	ili9320_write(lcd, ILI9320_POWER7, 0x000e);

	mdelay(100);

	ili9320_write(lcd, ILI9320_GRAM_HORIZ_ADDR, 0x00);
	ili9320_write(lcd, ILI9320_GRAM_VERT_ADD, 0x00);

	ret = ili9320_write_regs(lcd, vgg_gamma, ARRAY_SIZE(vgg_gamma));
	if (ret != 0)
		goto err_vgg3;

	ili9320_write(lcd, ILI9320_HORIZ_START, 0x0);
	ili9320_write(lcd, ILI9320_HORIZ_END, cfg->hsize - 1);
	ili9320_write(lcd, ILI9320_VERT_START, 0x0);
	ili9320_write(lcd, ILI9320_VERT_END, cfg->vsize - 1);

	ili9320_write(lcd, ILI9320_DRIVER2,
		      ILI9320_DRIVER2_NL(((cfg->vsize - 240) / 8) + 0x1D));

	ili9320_write(lcd, ILI9320_BASE_IMAGE, 0x1);
	ili9320_write(lcd, ILI9320_VERT_SCROLL, 0x00);

	for (addr = ILI9320_PARTIAL1_POSITION; addr <= ILI9320_PARTIAL2_END;
	     addr++) {
		ili9320_write(lcd, addr, 0x0);
	}

	ili9320_write(lcd, ILI9320_INTERFACE1, 0x10);
	ili9320_write(lcd, ILI9320_INTERFACE2, cfg->interface2);
	ili9320_write(lcd, ILI9320_INTERFACE3, cfg->interface3);
	ili9320_write(lcd, ILI9320_INTERFACE4, cfg->interface4);
	ili9320_write(lcd, ILI9320_INTERFACE5, cfg->interface5);
	ili9320_write(lcd, ILI9320_INTERFACE6, cfg->interface6);

	lcd->display1 = (ILI9320_DISPLAY1_D(3) | ILI9320_DISPLAY1_DTE |
			 ILI9320_DISPLAY1_GON | ILI9320_DISPLAY1_BASEE |
			 0x40);

	ili9320_write(lcd, ILI9320_DISPLAY1, lcd->display1);

	return 0;

 err_vgg3:
 err_vgg2:
 err_vgg:
 err_initial:
	return ret;
}