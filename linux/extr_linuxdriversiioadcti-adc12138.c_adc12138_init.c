#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct adc12138 {int acquisition_time; TYPE_1__* spi; int /*<<< orphan*/  complete; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC12138_MODE_ACQUISITION_TIME_10 ; 
 int /*<<< orphan*/  ADC12138_MODE_ACQUISITION_TIME_18 ; 
 int /*<<< orphan*/  ADC12138_MODE_ACQUISITION_TIME_34 ; 
 int /*<<< orphan*/  ADC12138_MODE_ACQUISITION_TIME_6 ; 
 int /*<<< orphan*/  ADC12138_MODE_AUTO_CAL ; 
 int ADC12138_STATUS_CAL ; 
 int EINVAL ; 
 int EIO ; 
 int adc12138_mode_programming (struct adc12138*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int adc12138_read_status (struct adc12138*) ; 
 int /*<<< orphan*/  adc12138_wait_eoc (struct adc12138*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adc12138_init(struct adc12138 *adc)
{
	int ret;
	int status;
	u8 mode;
	u8 trash;

	reinit_completion(&adc->complete);

	ret = adc12138_mode_programming(adc, ADC12138_MODE_AUTO_CAL, &trash, 1);
	if (ret)
		return ret;

	/* data output at this time has no significance */
	status = adc12138_read_status(adc);
	if (status < 0)
		return status;

	adc12138_wait_eoc(adc, msecs_to_jiffies(100));

	status = adc12138_read_status(adc);
	if (status & ADC12138_STATUS_CAL) {
		dev_warn(&adc->spi->dev,
			"Auto Cal sequence is still in progress: %#x\n",
			status);
		return -EIO;
	}

	switch (adc->acquisition_time) {
	case 6:
		mode = ADC12138_MODE_ACQUISITION_TIME_6;
		break;
	case 10:
		mode = ADC12138_MODE_ACQUISITION_TIME_10;
		break;
	case 18:
		mode = ADC12138_MODE_ACQUISITION_TIME_18;
		break;
	case 34:
		mode = ADC12138_MODE_ACQUISITION_TIME_34;
		break;
	default:
		return -EINVAL;
	}

	return adc12138_mode_programming(adc, mode, &trash, 1);
}