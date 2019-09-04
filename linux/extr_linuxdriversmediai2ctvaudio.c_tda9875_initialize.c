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
struct CHIPSTATE {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TDA9875_ABA ; 
 int /*<<< orphan*/  TDA9875_ACS ; 
 int /*<<< orphan*/  TDA9875_ADCIS ; 
 int /*<<< orphan*/  TDA9875_AER ; 
 int /*<<< orphan*/  TDA9875_ATR ; 
 int /*<<< orphan*/  TDA9875_AVL ; 
 int /*<<< orphan*/  TDA9875_AVR ; 
 int /*<<< orphan*/  TDA9875_C1LSB ; 
 int /*<<< orphan*/  TDA9875_C1MIB ; 
 int /*<<< orphan*/  TDA9875_C1MSB ; 
 int /*<<< orphan*/  TDA9875_C2LSB ; 
 int /*<<< orphan*/  TDA9875_C2MIB ; 
 int /*<<< orphan*/  TDA9875_C2MSB ; 
 int /*<<< orphan*/  TDA9875_CFG ; 
 int /*<<< orphan*/  TDA9875_CH1V ; 
 int /*<<< orphan*/  TDA9875_CH2V ; 
 int /*<<< orphan*/  TDA9875_DACOS ; 
 int /*<<< orphan*/  TDA9875_DCR ; 
 int /*<<< orphan*/  TDA9875_DEEM ; 
 int /*<<< orphan*/  TDA9875_FMAT ; 
 int /*<<< orphan*/  TDA9875_LOSR ; 
 int /*<<< orphan*/  TDA9875_MBA ; 
 int /*<<< orphan*/  TDA9875_MCS ; 
 int /*<<< orphan*/  TDA9875_MSR ; 
 int /*<<< orphan*/  TDA9875_MTR ; 
 int /*<<< orphan*/  TDA9875_MUT ; 
 int /*<<< orphan*/  TDA9875_MVL ; 
 int /*<<< orphan*/  TDA9875_MVR ; 
 int /*<<< orphan*/  TDA9875_SC1 ; 
 int /*<<< orphan*/  TDA9875_SC2 ; 
 int /*<<< orphan*/  chip_write (struct CHIPSTATE*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tda9875_initialize(struct CHIPSTATE *chip)
{
	chip_write(chip, TDA9875_CFG, 0xd0); /*reg de config 0 (reset)*/
	chip_write(chip, TDA9875_MSR, 0x03);    /* Monitor 0b00000XXX*/
	chip_write(chip, TDA9875_C1MSB, 0x00);  /*Car1(FM) MSB XMHz*/
	chip_write(chip, TDA9875_C1MIB, 0x00);  /*Car1(FM) MIB XMHz*/
	chip_write(chip, TDA9875_C1LSB, 0x00);  /*Car1(FM) LSB XMHz*/
	chip_write(chip, TDA9875_C2MSB, 0x00);  /*Car2(NICAM) MSB XMHz*/
	chip_write(chip, TDA9875_C2MIB, 0x00);  /*Car2(NICAM) MIB XMHz*/
	chip_write(chip, TDA9875_C2LSB, 0x00);  /*Car2(NICAM) LSB XMHz*/
	chip_write(chip, TDA9875_DCR, 0x00);    /*Demod config 0x00*/
	chip_write(chip, TDA9875_DEEM, 0x44);   /*DE-Emph 0b0100 0100*/
	chip_write(chip, TDA9875_FMAT, 0x00);   /*FM Matrix reg 0x00*/
	chip_write(chip, TDA9875_SC1, 0x00);    /* SCART 1 (SC1)*/
	chip_write(chip, TDA9875_SC2, 0x01);    /* SCART 2 (sc2)*/

	chip_write(chip, TDA9875_CH1V, 0x10);  /* Channel volume 1 mute*/
	chip_write(chip, TDA9875_CH2V, 0x10);  /* Channel volume 2 mute */
	chip_write(chip, TDA9875_DACOS, 0x02); /* sig DAC i/o(in:nicam)*/
	chip_write(chip, TDA9875_ADCIS, 0x6f); /* sig ADC input(in:mono)*/
	chip_write(chip, TDA9875_LOSR, 0x00);  /* line out (in:mono)*/
	chip_write(chip, TDA9875_AER, 0x00);   /*06 Effect (AVL+PSEUDO) */
	chip_write(chip, TDA9875_MCS, 0x44);   /* Main ch select (DAC) */
	chip_write(chip, TDA9875_MVL, 0x03);   /* Vol Main left 10dB */
	chip_write(chip, TDA9875_MVR, 0x03);   /* Vol Main right 10dB*/
	chip_write(chip, TDA9875_MBA, 0x00);   /* Main Bass Main 0dB*/
	chip_write(chip, TDA9875_MTR, 0x00);   /* Main Treble Main 0dB*/
	chip_write(chip, TDA9875_ACS, 0x44);   /* Aux chan select (dac)*/
	chip_write(chip, TDA9875_AVL, 0x00);   /* Vol Aux left 0dB*/
	chip_write(chip, TDA9875_AVR, 0x00);   /* Vol Aux right 0dB*/
	chip_write(chip, TDA9875_ABA, 0x00);   /* Aux Bass Main 0dB*/
	chip_write(chip, TDA9875_ATR, 0x00);   /* Aux Aigus Main 0dB*/

	chip_write(chip, TDA9875_MUT, 0xcc);   /* General mute  */
	return 0;
}