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
struct cpcap_adc_request {int channel; int bank_index; scalar_t__ result; struct cpcap_adc_phasing_tbl* phase_tbl; struct cpcap_adc_conversion_tbl* conv_tbl; } ;
struct cpcap_adc_phasing_tbl {scalar_t__ multiplier; scalar_t__ divider; scalar_t__ min; scalar_t__ max; int /*<<< orphan*/  offset; } ;
struct cpcap_adc_conversion_tbl {int /*<<< orphan*/  align_offset; int /*<<< orphan*/  cal_offset; } ;

/* Variables and functions */
#define  CPCAP_ADC_BATTI_PI17 130 
#define  CPCAP_ADC_BATTP 129 
#define  CPCAP_ADC_BATTP_PI16 128 
 int /*<<< orphan*/  CPCAP_FOUR_POINT_TWO_ADC ; 

__attribute__((used)) static void cpcap_adc_phase(struct cpcap_adc_request *req)
{
	const struct cpcap_adc_conversion_tbl *conv_tbl = req->conv_tbl;
	const struct cpcap_adc_phasing_tbl *phase_tbl = req->phase_tbl;
	int index = req->channel;

	/* Remuxed channels 16 and 17 use BATTP and BATTI entries */
	switch (req->channel) {
	case CPCAP_ADC_BATTP:
	case CPCAP_ADC_BATTP_PI16:
		index = req->bank_index;
		req->result -= phase_tbl[index].offset;
		req->result -= CPCAP_FOUR_POINT_TWO_ADC;
		req->result *= phase_tbl[index].multiplier;
		if (phase_tbl[index].divider == 0)
			return;
		req->result /= phase_tbl[index].divider;
		req->result += CPCAP_FOUR_POINT_TWO_ADC;
		break;
	case CPCAP_ADC_BATTI_PI17:
		index = req->bank_index;
		/* fallthrough */
	default:
		req->result += conv_tbl[index].cal_offset;
		req->result += conv_tbl[index].align_offset;
		req->result *= phase_tbl[index].multiplier;
		if (phase_tbl[index].divider == 0)
			return;
		req->result /= phase_tbl[index].divider;
		req->result += phase_tbl[index].offset;
		break;
	}

	if (req->result < phase_tbl[index].min)
		req->result = phase_tbl[index].min;
	else if (req->result > phase_tbl[index].max)
		req->result = phase_tbl[index].max;
}