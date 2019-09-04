#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct charlcd {int height; int width; int bwidth; int hwidth; int /*<<< orphan*/ * char_conv; int /*<<< orphan*/ * ops; } ;
struct TYPE_3__ {scalar_t__ e; scalar_t__ rs; scalar_t__ bl; scalar_t__ cl; scalar_t__ da; scalar_t__ rw; } ;
struct TYPE_4__ {scalar_t__ proto; scalar_t__ charset; int initialized; struct charlcd* charlcd; TYPE_1__ pins; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_LCD_BWIDTH ; 
 void* DEFAULT_LCD_CHARSET ; 
 scalar_t__ DEFAULT_LCD_HEIGHT ; 
 scalar_t__ DEFAULT_LCD_HWIDTH ; 
 scalar_t__ DEFAULT_LCD_PIN_BL ; 
 scalar_t__ DEFAULT_LCD_PIN_E ; 
 scalar_t__ DEFAULT_LCD_PIN_RS ; 
 scalar_t__ DEFAULT_LCD_PIN_RW ; 
 scalar_t__ DEFAULT_LCD_PIN_SCL ; 
 scalar_t__ DEFAULT_LCD_PIN_SDA ; 
 scalar_t__ DEFAULT_LCD_PROTO ; 
 scalar_t__ DEFAULT_LCD_WIDTH ; 
 size_t LCD_BIT_BL ; 
 size_t LCD_BIT_CL ; 
 size_t LCD_BIT_DA ; 
 size_t LCD_BIT_E ; 
 size_t LCD_BIT_RS ; 
 size_t LCD_BIT_RW ; 
 scalar_t__ LCD_CHARSET_KS0074 ; 
 void* LCD_CHARSET_NORMAL ; 
 size_t LCD_PORT_C ; 
 size_t LCD_PORT_D ; 
 scalar_t__ LCD_PROTO_PARALLEL ; 
 scalar_t__ LCD_PROTO_SERIAL ; 
#define  LCD_TYPE_CUSTOM 132 
#define  LCD_TYPE_HANTRONIX 131 
#define  LCD_TYPE_KS0074 130 
#define  LCD_TYPE_NEXCOM 129 
#define  LCD_TYPE_OLD 128 
 scalar_t__ NOT_SET ; 
 void* PIN_AUTOLF ; 
 scalar_t__ PIN_D0 ; 
 scalar_t__ PIN_INITP ; 
 void* PIN_NONE ; 
 scalar_t__ PIN_NOT_SET ; 
 void* PIN_SELECP ; 
 void* PIN_STROBE ; 
 struct charlcd* charlcd_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  charlcd_parallel_ops ; 
 int /*<<< orphan*/  charlcd_serial_ops ; 
 int /*<<< orphan*/  charlcd_tilcd_ops ; 
 TYPE_2__ lcd ; 
 int /*<<< orphan*/ ** lcd_bits ; 
 scalar_t__ lcd_bl_pin ; 
 scalar_t__ lcd_bwidth ; 
 int /*<<< orphan*/ * lcd_char_conv_ks0074 ; 
 scalar_t__ lcd_charset ; 
 scalar_t__ lcd_cl_pin ; 
 scalar_t__ lcd_da_pin ; 
 scalar_t__ lcd_e_pin ; 
 scalar_t__ lcd_height ; 
 scalar_t__ lcd_hwidth ; 
 scalar_t__ lcd_proto ; 
 scalar_t__ lcd_rs_pin ; 
 scalar_t__ lcd_rw_pin ; 
 scalar_t__ lcd_width ; 
 int /*<<< orphan*/  pin_to_bits (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int selected_lcd_type ; 

__attribute__((used)) static void lcd_init(void)
{
	struct charlcd *charlcd;

	charlcd = charlcd_alloc(0);
	if (!charlcd)
		return;

	/*
	 * Init lcd struct with load-time values to preserve exact
	 * current functionality (at least for now).
	 */
	charlcd->height = lcd_height;
	charlcd->width = lcd_width;
	charlcd->bwidth = lcd_bwidth;
	charlcd->hwidth = lcd_hwidth;

	switch (selected_lcd_type) {
	case LCD_TYPE_OLD:
		/* parallel mode, 8 bits */
		lcd.proto = LCD_PROTO_PARALLEL;
		lcd.charset = LCD_CHARSET_NORMAL;
		lcd.pins.e = PIN_STROBE;
		lcd.pins.rs = PIN_AUTOLF;

		charlcd->width = 40;
		charlcd->bwidth = 40;
		charlcd->hwidth = 64;
		charlcd->height = 2;
		break;
	case LCD_TYPE_KS0074:
		/* serial mode, ks0074 */
		lcd.proto = LCD_PROTO_SERIAL;
		lcd.charset = LCD_CHARSET_KS0074;
		lcd.pins.bl = PIN_AUTOLF;
		lcd.pins.cl = PIN_STROBE;
		lcd.pins.da = PIN_D0;

		charlcd->width = 16;
		charlcd->bwidth = 40;
		charlcd->hwidth = 16;
		charlcd->height = 2;
		break;
	case LCD_TYPE_NEXCOM:
		/* parallel mode, 8 bits, generic */
		lcd.proto = LCD_PROTO_PARALLEL;
		lcd.charset = LCD_CHARSET_NORMAL;
		lcd.pins.e = PIN_AUTOLF;
		lcd.pins.rs = PIN_SELECP;
		lcd.pins.rw = PIN_INITP;

		charlcd->width = 16;
		charlcd->bwidth = 40;
		charlcd->hwidth = 64;
		charlcd->height = 2;
		break;
	case LCD_TYPE_CUSTOM:
		/* customer-defined */
		lcd.proto = DEFAULT_LCD_PROTO;
		lcd.charset = DEFAULT_LCD_CHARSET;
		/* default geometry will be set later */
		break;
	case LCD_TYPE_HANTRONIX:
		/* parallel mode, 8 bits, hantronix-like */
	default:
		lcd.proto = LCD_PROTO_PARALLEL;
		lcd.charset = LCD_CHARSET_NORMAL;
		lcd.pins.e = PIN_STROBE;
		lcd.pins.rs = PIN_SELECP;

		charlcd->width = 16;
		charlcd->bwidth = 40;
		charlcd->hwidth = 64;
		charlcd->height = 2;
		break;
	}

	/* Overwrite with module params set on loading */
	if (lcd_height != NOT_SET)
		charlcd->height = lcd_height;
	if (lcd_width != NOT_SET)
		charlcd->width = lcd_width;
	if (lcd_bwidth != NOT_SET)
		charlcd->bwidth = lcd_bwidth;
	if (lcd_hwidth != NOT_SET)
		charlcd->hwidth = lcd_hwidth;
	if (lcd_charset != NOT_SET)
		lcd.charset = lcd_charset;
	if (lcd_proto != NOT_SET)
		lcd.proto = lcd_proto;
	if (lcd_e_pin != PIN_NOT_SET)
		lcd.pins.e = lcd_e_pin;
	if (lcd_rs_pin != PIN_NOT_SET)
		lcd.pins.rs = lcd_rs_pin;
	if (lcd_rw_pin != PIN_NOT_SET)
		lcd.pins.rw = lcd_rw_pin;
	if (lcd_cl_pin != PIN_NOT_SET)
		lcd.pins.cl = lcd_cl_pin;
	if (lcd_da_pin != PIN_NOT_SET)
		lcd.pins.da = lcd_da_pin;
	if (lcd_bl_pin != PIN_NOT_SET)
		lcd.pins.bl = lcd_bl_pin;

	/* this is used to catch wrong and default values */
	if (charlcd->width <= 0)
		charlcd->width = DEFAULT_LCD_WIDTH;
	if (charlcd->bwidth <= 0)
		charlcd->bwidth = DEFAULT_LCD_BWIDTH;
	if (charlcd->hwidth <= 0)
		charlcd->hwidth = DEFAULT_LCD_HWIDTH;
	if (charlcd->height <= 0)
		charlcd->height = DEFAULT_LCD_HEIGHT;

	if (lcd.proto == LCD_PROTO_SERIAL) {	/* SERIAL */
		charlcd->ops = &charlcd_serial_ops;

		if (lcd.pins.cl == PIN_NOT_SET)
			lcd.pins.cl = DEFAULT_LCD_PIN_SCL;
		if (lcd.pins.da == PIN_NOT_SET)
			lcd.pins.da = DEFAULT_LCD_PIN_SDA;

	} else if (lcd.proto == LCD_PROTO_PARALLEL) {	/* PARALLEL */
		charlcd->ops = &charlcd_parallel_ops;

		if (lcd.pins.e == PIN_NOT_SET)
			lcd.pins.e = DEFAULT_LCD_PIN_E;
		if (lcd.pins.rs == PIN_NOT_SET)
			lcd.pins.rs = DEFAULT_LCD_PIN_RS;
		if (lcd.pins.rw == PIN_NOT_SET)
			lcd.pins.rw = DEFAULT_LCD_PIN_RW;
	} else {
		charlcd->ops = &charlcd_tilcd_ops;
	}

	if (lcd.pins.bl == PIN_NOT_SET)
		lcd.pins.bl = DEFAULT_LCD_PIN_BL;

	if (lcd.pins.e == PIN_NOT_SET)
		lcd.pins.e = PIN_NONE;
	if (lcd.pins.rs == PIN_NOT_SET)
		lcd.pins.rs = PIN_NONE;
	if (lcd.pins.rw == PIN_NOT_SET)
		lcd.pins.rw = PIN_NONE;
	if (lcd.pins.bl == PIN_NOT_SET)
		lcd.pins.bl = PIN_NONE;
	if (lcd.pins.cl == PIN_NOT_SET)
		lcd.pins.cl = PIN_NONE;
	if (lcd.pins.da == PIN_NOT_SET)
		lcd.pins.da = PIN_NONE;

	if (lcd.charset == NOT_SET)
		lcd.charset = DEFAULT_LCD_CHARSET;

	if (lcd.charset == LCD_CHARSET_KS0074)
		charlcd->char_conv = lcd_char_conv_ks0074;
	else
		charlcd->char_conv = NULL;

	pin_to_bits(lcd.pins.e, lcd_bits[LCD_PORT_D][LCD_BIT_E],
		    lcd_bits[LCD_PORT_C][LCD_BIT_E]);
	pin_to_bits(lcd.pins.rs, lcd_bits[LCD_PORT_D][LCD_BIT_RS],
		    lcd_bits[LCD_PORT_C][LCD_BIT_RS]);
	pin_to_bits(lcd.pins.rw, lcd_bits[LCD_PORT_D][LCD_BIT_RW],
		    lcd_bits[LCD_PORT_C][LCD_BIT_RW]);
	pin_to_bits(lcd.pins.bl, lcd_bits[LCD_PORT_D][LCD_BIT_BL],
		    lcd_bits[LCD_PORT_C][LCD_BIT_BL]);
	pin_to_bits(lcd.pins.cl, lcd_bits[LCD_PORT_D][LCD_BIT_CL],
		    lcd_bits[LCD_PORT_C][LCD_BIT_CL]);
	pin_to_bits(lcd.pins.da, lcd_bits[LCD_PORT_D][LCD_BIT_DA],
		    lcd_bits[LCD_PORT_C][LCD_BIT_DA]);

	lcd.charlcd = charlcd;
	lcd.initialized = true;
}