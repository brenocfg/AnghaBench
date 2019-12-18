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

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int* log10x_x1000 ; 
 int* valx_x10 ; 

__attribute__((used)) static u32 log10_x1000(u32 x)
{
	u32 diff_val, step_val, step_log10;
	u32 log_val = 0;
	u32 i;

	if (x <= 0)
		return -1000000; /* signal error */

	if (x == 10)
		return 0; /* log(1)=0 */

	if (x < 10) {
		while (x < 10) {
			x = x * 10;
			log_val--;
		}
	} else {	/* x > 10 */
		while (x >= 100) {
			x = x / 10;
			log_val++;
		}
	}
	log_val *= 1000;

	if (x == 10) /* was our input an exact multiple of 10 */
		return log_val;	/* don't need to interpolate */

	/* find our place on the log curve */
	for (i = 1; i < ARRAY_SIZE(valx_x10); i++) {
		if (valx_x10[i] >= x)
			break;
	}
	if (i == ARRAY_SIZE(valx_x10))
		return log_val + log10x_x1000[i - 1];

	diff_val   = x - valx_x10[i-1];
	step_val   = valx_x10[i] - valx_x10[i - 1];
	step_log10 = log10x_x1000[i] - log10x_x1000[i - 1];

	/* do a linear interpolation to get in-between values */
	return log_val + log10x_x1000[i - 1] +
		((diff_val*step_log10) / step_val);
}