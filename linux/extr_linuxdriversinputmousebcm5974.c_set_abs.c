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
struct input_dev {int dummy; } ;
struct bcm5974_param {int snratio; int max; int min; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,unsigned int,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_abs(struct input_dev *input, unsigned int code,
		    const struct bcm5974_param *p)
{
	int fuzz = p->snratio ? (p->max - p->min) / p->snratio : 0;
	input_set_abs_params(input, code, p->min, p->max, fuzz, 0);
}