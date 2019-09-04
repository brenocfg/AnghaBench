#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pm8941_pwrkey {int /*<<< orphan*/  input; TYPE_1__* data; int /*<<< orphan*/  code; scalar_t__ baseaddr; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {unsigned int status_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ PON_RT_STS ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 

__attribute__((used)) static irqreturn_t pm8941_pwrkey_irq(int irq, void *_data)
{
	struct pm8941_pwrkey *pwrkey = _data;
	unsigned int sts;
	int error;

	error = regmap_read(pwrkey->regmap,
			    pwrkey->baseaddr + PON_RT_STS, &sts);
	if (error)
		return IRQ_HANDLED;

	input_report_key(pwrkey->input, pwrkey->code,
			 sts & pwrkey->data->status_bit);
	input_sync(pwrkey->input);

	return IRQ_HANDLED;
}