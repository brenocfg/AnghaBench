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
typedef  int /*<<< orphan*/  uint16_t ;
struct xadc {int dummy; } ;

/* Variables and functions */
#define  XADC_CONF1_SEQ_INDEPENDENT 129 
#define  XADC_CONF1_SEQ_SIMULTANEOUS 128 
 int /*<<< orphan*/  XADC_CONF2_PD_ADC_B ; 
 int /*<<< orphan*/  XADC_CONF2_PD_MASK ; 
 int /*<<< orphan*/  XADC_REG_CONF2 ; 
 int xadc_update_adc_reg (struct xadc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xadc_power_adc_b(struct xadc *xadc, unsigned int seq_mode)
{
	uint16_t val;

	switch (seq_mode) {
	case XADC_CONF1_SEQ_SIMULTANEOUS:
	case XADC_CONF1_SEQ_INDEPENDENT:
		val = XADC_CONF2_PD_ADC_B;
		break;
	default:
		val = 0;
		break;
	}

	return xadc_update_adc_reg(xadc, XADC_REG_CONF2, XADC_CONF2_PD_MASK,
		val);
}