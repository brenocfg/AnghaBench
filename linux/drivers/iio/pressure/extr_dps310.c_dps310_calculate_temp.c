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
struct dps310_data {scalar_t__ c1; scalar_t__ temp_raw; scalar_t__ c0; } ;
typedef  long long s64 ;

/* Variables and functions */
 long long div_s64 (long long,int) ; 
 int dps310_get_temp_k (struct dps310_data*) ; 

__attribute__((used)) static int dps310_calculate_temp(struct dps310_data *data)
{
	s64 c0;
	s64 t;
	int kt = dps310_get_temp_k(data);

	if (kt < 0)
		return kt;

	/* Obtain inverse-scaled offset */
	c0 = div_s64((s64)kt * (s64)data->c0, 2);

	/* Add the offset to the unscaled temperature */
	t = c0 + ((s64)data->temp_raw * (s64)data->c1);

	/* Convert to milliCelsius and scale the temperature */
	return (int)div_s64(t * 1000LL, kt);
}