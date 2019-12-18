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
struct cpcap_adc_request {int channel; int /*<<< orphan*/  result; struct cpcap_adc_conversion_tbl* conv_tbl; } ;
struct cpcap_adc_conversion_tbl {scalar_t__ conv_type; scalar_t__ conv_offset; int /*<<< orphan*/  divider; int /*<<< orphan*/  multiplier; } ;

/* Variables and functions */
 int CPCAP_ADC_AD0 ; 
 int CPCAP_ADC_AD3 ; 
 int CPCAP_ADC_BATTI ; 
#define  CPCAP_ADC_BATTI_PI17 129 
 int CPCAP_ADC_BATTP ; 
#define  CPCAP_ADC_BATTP_PI16 128 
 scalar_t__ IIO_CHAN_INFO_RAW ; 
 int /*<<< orphan*/  cpcap_adc_table_to_millicelcius (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpcap_adc_convert(struct cpcap_adc_request *req)
{
	const struct cpcap_adc_conversion_tbl *conv_tbl = req->conv_tbl;
	int index = req->channel;

	/* Remuxed channels 16 and 17 use BATTP and BATTI entries */
	switch (req->channel) {
	case CPCAP_ADC_BATTP_PI16:
		index = CPCAP_ADC_BATTP;
		break;
	case CPCAP_ADC_BATTI_PI17:
		index = CPCAP_ADC_BATTI;
		break;
	default:
		break;
	}

	/* No conversion for raw channels */
	if (conv_tbl[index].conv_type == IIO_CHAN_INFO_RAW)
		return;

	/* Temperatures use a lookup table instead of conversion table */
	if ((req->channel == CPCAP_ADC_AD0) ||
	    (req->channel == CPCAP_ADC_AD3)) {
		req->result =
			cpcap_adc_table_to_millicelcius(req->result);

		return;
	}

	/* All processed channels use a conversion table */
	req->result *= conv_tbl[index].multiplier;
	if (conv_tbl[index].divider == 0)
		return;
	req->result /= conv_tbl[index].divider;
	req->result += conv_tbl[index].conv_offset;
}