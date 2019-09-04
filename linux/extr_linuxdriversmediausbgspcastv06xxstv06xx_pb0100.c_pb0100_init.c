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
struct sd {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  PB_ADCGAINH ; 
 int /*<<< orphan*/  PB_ADCGAINL ; 
 int /*<<< orphan*/  PB_ADCGLOBALGAIN ; 
 int /*<<< orphan*/  PB_ADCMAXGAIN ; 
 int /*<<< orphan*/  PB_ADCMINGAIN ; 
 int /*<<< orphan*/  PB_CFILLIN ; 
 int /*<<< orphan*/  PB_CONTROL ; 
 int /*<<< orphan*/  PB_EXPGAIN ; 
 int /*<<< orphan*/  PB_FINTTIME ; 
 int /*<<< orphan*/  PB_PREADCTRL ; 
 int /*<<< orphan*/  PB_R15 ; 
 int /*<<< orphan*/  PB_R17 ; 
 int /*<<< orphan*/  PB_R28 ; 
 int /*<<< orphan*/  PB_R54 ; 
 int /*<<< orphan*/  PB_R55 ; 
 int /*<<< orphan*/  PB_RESET ; 
 int /*<<< orphan*/  PB_RINTTIME ; 
 int /*<<< orphan*/  PB_ROWSPEED ; 
 int /*<<< orphan*/  PB_UPDATEINT ; 
 int /*<<< orphan*/  PB_VBL ; 
 int /*<<< orphan*/  PB_VOFFSET ; 
 int /*<<< orphan*/  STV_REG00 ; 
 int /*<<< orphan*/  STV_REG01 ; 
 int /*<<< orphan*/  STV_REG02 ; 
 int /*<<< orphan*/  STV_REG03 ; 
 int /*<<< orphan*/  STV_REG04 ; 
 int /*<<< orphan*/  STV_SCAN_RATE ; 
 int /*<<< orphan*/  stv06xx_write_bridge (struct sd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stv06xx_write_sensor (struct sd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pb0100_init(struct sd *sd)
{
	stv06xx_write_bridge(sd, STV_REG00, 1);
	stv06xx_write_bridge(sd, STV_SCAN_RATE, 0);

	/* Reset sensor */
	stv06xx_write_sensor(sd, PB_RESET, 1);
	stv06xx_write_sensor(sd, PB_RESET, 0);

	/* Disable chip */
	stv06xx_write_sensor(sd, PB_CONTROL, BIT(5)|BIT(3));

	/* Gain stuff...*/
	stv06xx_write_sensor(sd, PB_PREADCTRL, BIT(12)|BIT(10)|BIT(6));
	stv06xx_write_sensor(sd, PB_ADCGLOBALGAIN, 12);

	/* Set up auto-exposure */
	/* ADC VREF_HI new setting for a transition
	  from the Expose1 to the Expose2 setting */
	stv06xx_write_sensor(sd, PB_R28, 12);
	/* gain max for autoexposure */
	stv06xx_write_sensor(sd, PB_ADCMAXGAIN, 180);
	/* gain min for autoexposure  */
	stv06xx_write_sensor(sd, PB_ADCMINGAIN, 12);
	/* Maximum frame integration time (programmed into R8)
	   allowed for auto-exposure routine */
	stv06xx_write_sensor(sd, PB_R54, 3);
	/* Minimum frame integration time (programmed into R8)
	   allowed for auto-exposure routine */
	stv06xx_write_sensor(sd, PB_R55, 0);
	stv06xx_write_sensor(sd, PB_UPDATEINT, 1);
	/* R15  Expose0 (maximum that auto-exposure may use) */
	stv06xx_write_sensor(sd, PB_R15, 800);
	/* R17  Expose2 (minimum that auto-exposure may use) */
	stv06xx_write_sensor(sd, PB_R17, 10);

	stv06xx_write_sensor(sd, PB_EXPGAIN, 0);

	/* 0x14 */
	stv06xx_write_sensor(sd, PB_VOFFSET, 0);
	/* 0x0D */
	stv06xx_write_sensor(sd, PB_ADCGAINH, 11);
	/* Set black level (important!) */
	stv06xx_write_sensor(sd, PB_ADCGAINL, 0);

	/* ??? */
	stv06xx_write_bridge(sd, STV_REG00, 0x11);
	stv06xx_write_bridge(sd, STV_REG03, 0x45);
	stv06xx_write_bridge(sd, STV_REG04, 0x07);

	/* Scan/timing for the sensor */
	stv06xx_write_sensor(sd, PB_ROWSPEED, BIT(4)|BIT(3)|BIT(1));
	stv06xx_write_sensor(sd, PB_CFILLIN, 14);
	stv06xx_write_sensor(sd, PB_VBL, 0);
	stv06xx_write_sensor(sd, PB_FINTTIME, 0);
	stv06xx_write_sensor(sd, PB_RINTTIME, 123);

	stv06xx_write_bridge(sd, STV_REG01, 0xc2);
	stv06xx_write_bridge(sd, STV_REG02, 0xb0);
	return 0;
}