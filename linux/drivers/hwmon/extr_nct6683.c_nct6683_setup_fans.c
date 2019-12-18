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
struct nct6683_data {int have_fan; int* fanin_cfg; int have_pwm; int* fanout_cfg; } ;

/* Variables and functions */
 int NCT6683_NUM_REG_FAN ; 
 int NCT6683_NUM_REG_PWM ; 
 int /*<<< orphan*/  NCT6683_REG_FANIN_CFG (int) ; 
 int /*<<< orphan*/  NCT6683_REG_FANOUT_CFG (int) ; 
 int nct6683_read (struct nct6683_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nct6683_setup_fans(struct nct6683_data *data)
{
	int i;
	u8 reg;

	for (i = 0; i < NCT6683_NUM_REG_FAN; i++) {
		reg = nct6683_read(data, NCT6683_REG_FANIN_CFG(i));
		if (reg & 0x80)
			data->have_fan |= 1 << i;
		data->fanin_cfg[i] = reg;
	}
	for (i = 0; i < NCT6683_NUM_REG_PWM; i++) {
		reg = nct6683_read(data, NCT6683_REG_FANOUT_CFG(i));
		if (reg & 0x80)
			data->have_pwm |= 1 << i;
		data->fanout_cfg[i] = reg;
	}
}