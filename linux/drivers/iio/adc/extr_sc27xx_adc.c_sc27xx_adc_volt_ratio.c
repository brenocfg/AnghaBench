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
typedef  int u32 ;
struct sc27xx_adc_data {int dummy; } ;

/* Variables and functions */
 int SC27XX_RATIO_DENOMINATOR_MASK ; 
 int SC27XX_RATIO_NUMERATOR_OFFSET ; 
 int sc27xx_adc_get_ratio (int,int) ; 

__attribute__((used)) static void sc27xx_adc_volt_ratio(struct sc27xx_adc_data *data,
				  int channel, int scale,
				  u32 *div_numerator, u32 *div_denominator)
{
	u32 ratio = sc27xx_adc_get_ratio(channel, scale);

	*div_numerator = ratio >> SC27XX_RATIO_NUMERATOR_OFFSET;
	*div_denominator = ratio & SC27XX_RATIO_DENOMINATOR_MASK;
}