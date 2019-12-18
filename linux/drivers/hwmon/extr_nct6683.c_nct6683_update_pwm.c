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
struct nct6683_data {int have_pwm; int /*<<< orphan*/ * pwm; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int NCT6683_NUM_REG_PWM ; 
 int /*<<< orphan*/  NCT6683_REG_PWM (int) ; 
 struct nct6683_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  nct6683_read (struct nct6683_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nct6683_update_pwm(struct device *dev)
{
	struct nct6683_data *data = dev_get_drvdata(dev);
	int i;

	for (i = 0; i < NCT6683_NUM_REG_PWM; i++) {
		if (!(data->have_pwm & (1 << i)))
			continue;
		data->pwm[i] = nct6683_read(data, NCT6683_REG_PWM(i));
	}
}