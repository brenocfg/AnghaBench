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
struct sh_mobile_i2c_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICCR ; 
 int /*<<< orphan*/  ICCR_ICE ; 
 int /*<<< orphan*/  ICCR_SCP ; 
 int /*<<< orphan*/  ICCR_TRS ; 
 int /*<<< orphan*/  ICSTART ; 
 int /*<<< orphan*/  ICSTART_ICSTART ; 
 int /*<<< orphan*/  iic_rd (struct sh_mobile_i2c_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iic_set_clr (struct sh_mobile_i2c_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iic_wr (struct sh_mobile_i2c_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sh_mobile_i2c_init (struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sh_mobile_i2c_r8a7740_workaround(struct sh_mobile_i2c_data *pd)
{
	iic_set_clr(pd, ICCR, ICCR_ICE, 0);
	iic_rd(pd, ICCR); /* dummy read */

	iic_set_clr(pd, ICSTART, ICSTART_ICSTART, 0);
	iic_rd(pd, ICSTART); /* dummy read */

	udelay(10);

	iic_wr(pd, ICCR, ICCR_SCP);
	iic_wr(pd, ICSTART, 0);

	udelay(10);

	iic_wr(pd, ICCR, ICCR_TRS);
	udelay(10);
	iic_wr(pd, ICCR, 0);
	udelay(10);
	iic_wr(pd, ICCR, ICCR_TRS);
	udelay(10);

	return sh_mobile_i2c_init(pd);
}