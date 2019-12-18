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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct lcd_device {int dummy; } ;
struct l4f00242t03_priv {int lcd_state; struct lcd_device* ld; struct spi_device* spi; } ;

/* Variables and functions */
 int FB_BLANK_NORMAL ; 
 int FB_BLANK_POWERDOWN ; 
 int FB_BLANK_UNBLANK ; 
 int FB_BLANK_VSYNC_SUSPEND ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  l4f00242t03_lcd_init (struct spi_device*) ; 
 int /*<<< orphan*/  l4f00242t03_lcd_powerdown (struct spi_device*) ; 
 struct l4f00242t03_priv* lcd_get_data (struct lcd_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spi_write (struct spi_device*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int l4f00242t03_lcd_power_set(struct lcd_device *ld, int power)
{
	struct l4f00242t03_priv *priv = lcd_get_data(ld);
	struct spi_device *spi = priv->spi;

	const u16 slpout = 0x11;
	const u16 dison = 0x29;

	const u16 slpin = 0x10;
	const u16 disoff = 0x28;

	if (power <= FB_BLANK_NORMAL) {
		if (priv->lcd_state <= FB_BLANK_NORMAL) {
			/* Do nothing, the LCD is running */
		} else if (priv->lcd_state < FB_BLANK_POWERDOWN) {
			dev_dbg(&spi->dev, "Resuming LCD\n");

			spi_write(spi, (const u8 *)&slpout, sizeof(u16));
			msleep(60);
			spi_write(spi, (const u8 *)&dison, sizeof(u16));
		} else {
			/* priv->lcd_state == FB_BLANK_POWERDOWN */
			l4f00242t03_lcd_init(spi);
			priv->lcd_state = FB_BLANK_VSYNC_SUSPEND;
			l4f00242t03_lcd_power_set(priv->ld, power);
		}
	} else if (power < FB_BLANK_POWERDOWN) {
		if (priv->lcd_state <= FB_BLANK_NORMAL) {
			/* Send the display in standby */
			dev_dbg(&spi->dev, "Standby the LCD\n");

			spi_write(spi, (const u8 *)&disoff, sizeof(u16));
			msleep(60);
			spi_write(spi, (const u8 *)&slpin, sizeof(u16));
		} else if (priv->lcd_state < FB_BLANK_POWERDOWN) {
			/* Do nothing, the LCD is already in standby */
		} else {
			/* priv->lcd_state == FB_BLANK_POWERDOWN */
			l4f00242t03_lcd_init(spi);
			priv->lcd_state = FB_BLANK_UNBLANK;
			l4f00242t03_lcd_power_set(ld, power);
		}
	} else {
		/* power == FB_BLANK_POWERDOWN */
		if (priv->lcd_state != FB_BLANK_POWERDOWN) {
			/* Clear the screen before shutting down */
			spi_write(spi, (const u8 *)&disoff, sizeof(u16));
			msleep(60);
			l4f00242t03_lcd_powerdown(spi);
		}
	}

	priv->lcd_state = power;

	return 0;
}