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

/* Variables and functions */
 int MODE_PIN0 ; 
 int MODE_PIN1 ; 
 int MODE_PIN10 ; 
 int MODE_PIN11 ; 
 int MODE_PIN12 ; 
 int MODE_PIN13 ; 
 int MODE_PIN14 ; 
 int MODE_PIN2 ; 
 int MODE_PIN3 ; 
 int MODE_PIN4 ; 
 int MODE_PIN5 ; 
 int MODE_PIN6 ; 
 int MODE_PIN7 ; 
 int MODE_PIN8 ; 
 int MODE_PIN9 ; 

__attribute__((used)) static int apsh4ad0a_mode_pins(void)
{
	int value = 0;

	/* These are the factory default settings of SW1 and SW2.
	 * If you change these dip switches then you will need to
	 * adjust the values below as well.
	 */
	value |=  MODE_PIN0;  /* Clock Mode 3 */
	value |=  MODE_PIN1;
	value &= ~MODE_PIN2;
	value &= ~MODE_PIN3;
	value &= ~MODE_PIN4;  /* 16-bit Area0 bus width  */
	value |=  MODE_PIN5;
	value |=  MODE_PIN6;
	value |=  MODE_PIN7;  /* Normal mode */
	value |=  MODE_PIN8;  /* Little Endian */
	value |=  MODE_PIN9;  /* Crystal resonator */
	value &= ~MODE_PIN10; /* 29-bit address mode */
	value &= ~MODE_PIN11; /* PCI-E Root port */
	value &= ~MODE_PIN12; /* 4 lane + 1 lane */
	value |=  MODE_PIN13; /* AUD Enable */
	value &= ~MODE_PIN14; /* Normal Operation */

	return value;
}