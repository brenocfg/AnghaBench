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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int len; } ;
struct adc084s021 {int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/  message; int /*<<< orphan*/  spi; TYPE_1__ spi_trans; } ;

/* Variables and functions */
 int spi_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adc084s021_adc_conversion(struct adc084s021 *adc, void *data)
{
	int n_words = (adc->spi_trans.len >> 1) - 1; /* Discard first word */
	int ret, i = 0;
	u16 *p = data;

	/* Do the transfer */
	ret = spi_sync(adc->spi, &adc->message);
	if (ret < 0)
		return ret;

	for (; i < n_words; i++)
		*(p + i) = adc->rx_buf[i + 1];

	return ret;
}