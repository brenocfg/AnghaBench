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
typedef  int /*<<< orphan*/  u32 ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stv0367cab_get_mclk (struct dvb_frontend*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 stv0367cab_get_adc_freq(struct dvb_frontend *fe, u32 ExtClk_Hz)
{
	u32 ADCClk_Hz = ExtClk_Hz;

	ADCClk_Hz = stv0367cab_get_mclk(fe, ExtClk_Hz);

	return ADCClk_Hz;
}