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
struct adc12138 {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ADC12138_MODE_READ_STATUS ; 
 int adc12138_mode_programming (struct adc12138*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int adc12138_read_conv_data(struct adc12138 *adc, __be16 *value)
{
	/* Issue a read status instruction and read previous conversion data */
	return adc12138_mode_programming(adc, ADC12138_MODE_READ_STATUS,
					 value, sizeof(*value));
}