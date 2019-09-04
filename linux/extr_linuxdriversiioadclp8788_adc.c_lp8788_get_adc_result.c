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
typedef  int u8 ;
struct lp8788_adc {int /*<<< orphan*/  lp; } ;
typedef  enum lp8788_adc_id { ____Placeholder_lp8788_adc_id } lp8788_adc_id ;

/* Variables and functions */
 int ADC_CONV_START ; 
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  LP8788_ADC_CONF ; 
 int /*<<< orphan*/  LP8788_ADC_DONE ; 
 int /*<<< orphan*/  LP8788_ADC_RAW ; 
 int lp8788_read_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int lp8788_read_multi_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int lp8788_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int lp8788_get_adc_result(struct lp8788_adc *adc, enum lp8788_adc_id id,
				int *val)
{
	unsigned int msb;
	unsigned int lsb;
	unsigned int result;
	u8 data;
	u8 rawdata[2];
	int size = ARRAY_SIZE(rawdata);
	int retry = 5;
	int ret;

	data = (id << 1) | ADC_CONV_START;
	ret = lp8788_write_byte(adc->lp, LP8788_ADC_CONF, data);
	if (ret)
		goto err_io;

	/* retry until adc conversion is done */
	data = 0;
	while (retry--) {
		usleep_range(100, 200);

		ret = lp8788_read_byte(adc->lp, LP8788_ADC_DONE, &data);
		if (ret)
			goto err_io;

		/* conversion done */
		if (data)
			break;
	}

	ret = lp8788_read_multi_bytes(adc->lp, LP8788_ADC_RAW, rawdata, size);
	if (ret)
		goto err_io;

	msb = (rawdata[0] << 4) & 0x00000ff0;
	lsb = (rawdata[1] >> 4) & 0x0000000f;
	result = msb | lsb;
	*val = result;

	return 0;

err_io:
	return ret;
}