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
struct rpi_touchscreen {int dummy; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DSI_LANEENABLE ; 
 int DSI_LANEENABLE_CLOCK ; 
 int DSI_LANEENABLE_D0 ; 
 int /*<<< orphan*/  DSI_STARTDSI ; 
 int /*<<< orphan*/  LCDCTRL ; 
 int /*<<< orphan*/  PPI_D0S_ATMR ; 
 int /*<<< orphan*/  PPI_D0S_CLRSIPOCOUNT ; 
 int /*<<< orphan*/  PPI_D1S_ATMR ; 
 int /*<<< orphan*/  PPI_D1S_CLRSIPOCOUNT ; 
 int /*<<< orphan*/  PPI_LPTXTIMECNT ; 
 int /*<<< orphan*/  PPI_STARTPPI ; 
 int /*<<< orphan*/  REG_PORTA ; 
 int /*<<< orphan*/  REG_PORTB ; 
 int /*<<< orphan*/  REG_POWERON ; 
 int /*<<< orphan*/  REG_PWM ; 
 int /*<<< orphan*/  SPICMR ; 
 int /*<<< orphan*/  SYSCTRL ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct rpi_touchscreen* panel_to_ts (struct drm_panel*) ; 
 int rpi_touchscreen_i2c_read (struct rpi_touchscreen*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpi_touchscreen_i2c_write (struct rpi_touchscreen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rpi_touchscreen_write (struct rpi_touchscreen*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rpi_touchscreen_enable(struct drm_panel *panel)
{
	struct rpi_touchscreen *ts = panel_to_ts(panel);
	int i;

	rpi_touchscreen_i2c_write(ts, REG_POWERON, 1);
	/* Wait for nPWRDWN to go low to indicate poweron is done. */
	for (i = 0; i < 100; i++) {
		if (rpi_touchscreen_i2c_read(ts, REG_PORTB) & 1)
			break;
	}

	rpi_touchscreen_write(ts, DSI_LANEENABLE,
			      DSI_LANEENABLE_CLOCK |
			      DSI_LANEENABLE_D0);
	rpi_touchscreen_write(ts, PPI_D0S_CLRSIPOCOUNT, 0x05);
	rpi_touchscreen_write(ts, PPI_D1S_CLRSIPOCOUNT, 0x05);
	rpi_touchscreen_write(ts, PPI_D0S_ATMR, 0x00);
	rpi_touchscreen_write(ts, PPI_D1S_ATMR, 0x00);
	rpi_touchscreen_write(ts, PPI_LPTXTIMECNT, 0x03);

	rpi_touchscreen_write(ts, SPICMR, 0x00);
	rpi_touchscreen_write(ts, LCDCTRL, 0x00100150);
	rpi_touchscreen_write(ts, SYSCTRL, 0x040f);
	msleep(100);

	rpi_touchscreen_write(ts, PPI_STARTPPI, 0x01);
	rpi_touchscreen_write(ts, DSI_STARTDSI, 0x01);
	msleep(100);

	/* Turn on the backlight. */
	rpi_touchscreen_i2c_write(ts, REG_PWM, 255);

	/* Default to the same orientation as the closed source
	 * firmware used for the panel.  Runtime rotation
	 * configuration will be supported using VC4's plane
	 * orientation bits.
	 */
	rpi_touchscreen_i2c_write(ts, REG_PORTA, BIT(2));

	return 0;
}