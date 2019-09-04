#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct iio_dev {int dummy; } ;
struct exynos_adc {int /*<<< orphan*/  regs; TYPE_1__* input; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {scalar_t__ users; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int ADC_DATX_MASK ; 
 int ADC_DATX_PRESSED ; 
 int ADC_DATY_MASK ; 
 int /*<<< orphan*/  ADC_V1_CLRINTPNDNUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct iio_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int exynos_read_s3c64xx_ts (struct iio_dev*,int*,int*) ; 
 int /*<<< orphan*/  input_report_abs (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t exynos_ts_isr(int irq, void *dev_id)
{
	struct exynos_adc *info = dev_id;
	struct iio_dev *dev = dev_get_drvdata(info->dev);
	u32 x, y;
	bool pressed;
	int ret;

	while (info->input->users) {
		ret = exynos_read_s3c64xx_ts(dev, &x, &y);
		if (ret == -ETIMEDOUT)
			break;

		pressed = x & y & ADC_DATX_PRESSED;
		if (!pressed) {
			input_report_key(info->input, BTN_TOUCH, 0);
			input_sync(info->input);
			break;
		}

		input_report_abs(info->input, ABS_X, x & ADC_DATX_MASK);
		input_report_abs(info->input, ABS_Y, y & ADC_DATY_MASK);
		input_report_key(info->input, BTN_TOUCH, 1);
		input_sync(info->input);

		usleep_range(1000, 1100);
	};

	writel(0, ADC_V1_CLRINTPNDNUP(info->regs));

	return IRQ_HANDLED;
}