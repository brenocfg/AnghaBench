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
struct adc128 {int* buffer; int /*<<< orphan*/  lock; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_read (int /*<<< orphan*/ ,int**,int) ; 
 int spi_write (int /*<<< orphan*/ ,int**,int) ; 

__attribute__((used)) static int adc128_adc_conversion(struct adc128 *adc, u8 channel)
{
	int ret;

	mutex_lock(&adc->lock);

	adc->buffer[0] = channel << 3;
	adc->buffer[1] = 0;

	ret = spi_write(adc->spi, &adc->buffer, 2);
	if (ret < 0) {
		mutex_unlock(&adc->lock);
		return ret;
	}

	ret = spi_read(adc->spi, &adc->buffer, 2);

	mutex_unlock(&adc->lock);

	if (ret < 0)
		return ret;

	return ((adc->buffer[0] << 8 | adc->buffer[1]) & 0xFFF);
}