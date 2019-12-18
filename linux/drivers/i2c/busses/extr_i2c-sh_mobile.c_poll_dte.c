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
typedef  int u_int8_t ;
struct sh_mobile_i2c_data {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ICSR ; 
 int ICSR_DTE ; 
 int ICSR_TACK ; 
 int iic_rd (struct sh_mobile_i2c_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int poll_dte(struct sh_mobile_i2c_data *pd)
{
	int i;

	for (i = 1000; i; i--) {
		u_int8_t val = iic_rd(pd, ICSR);

		if (val & ICSR_DTE)
			break;

		if (val & ICSR_TACK)
			return -ENXIO;

		udelay(10);
	}

	return i ? 0 : -ETIMEDOUT;
}