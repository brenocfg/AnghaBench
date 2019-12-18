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
typedef  int u32 ;
struct stv0900_internal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TNRLD ; 
 int /*<<< orphan*/  TUN_BW ; 
 int /*<<< orphan*/  TUN_RFFREQ0 ; 
 int /*<<< orphan*/  TUN_RFFREQ1 ; 
 int /*<<< orphan*/  TUN_RFFREQ2 ; 
 int /*<<< orphan*/  stv0900_write_bits (struct stv0900_internal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stv0900_write_reg (struct stv0900_internal*,int /*<<< orphan*/ ,int) ; 

void stv0900_set_tuner_auto(struct stv0900_internal *intp, u32 Frequency,
						u32 Bandwidth, int demod)
{
	u32 tunerFrequency;
	/* Formulat:
	Tuner_frequency_reg= Frequency(MHz)*64
	*/
	tunerFrequency = (Frequency * 64) / 1000;

	stv0900_write_bits(intp, TUN_RFFREQ2, (tunerFrequency >> 10));
	stv0900_write_bits(intp, TUN_RFFREQ1, (tunerFrequency >> 2) & 0xff);
	stv0900_write_bits(intp, TUN_RFFREQ0, (tunerFrequency & 0x03));
	/* Low Pass Filter = BW /2 (MHz)*/
	stv0900_write_bits(intp, TUN_BW, Bandwidth / 2000000);
	/* Tuner Write trig */
	stv0900_write_reg(intp, TNRLD, 1);
}