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
struct adc12138 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC12138_MODE_READ_STATUS ; 
 int adc12138_mode_programming (struct adc12138*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int adc12138_read_status(struct adc12138 *adc)
{
	u8 rx_buf[2];
	int ret;

	ret = adc12138_mode_programming(adc, ADC12138_MODE_READ_STATUS,
					rx_buf, 2);
	if (ret)
		return ret;

	return (rx_buf[0] << 1) | (rx_buf[1] >> 7);
}