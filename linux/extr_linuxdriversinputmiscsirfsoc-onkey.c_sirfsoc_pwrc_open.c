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
struct sirfsoc_pwrc_drvdata {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct sirfsoc_pwrc_drvdata* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  sirfsoc_pwrc_toggle_interrupts (struct sirfsoc_pwrc_drvdata*,int) ; 

__attribute__((used)) static int sirfsoc_pwrc_open(struct input_dev *input)
{
	struct sirfsoc_pwrc_drvdata *pwrcdrv = input_get_drvdata(input);

	sirfsoc_pwrc_toggle_interrupts(pwrcdrv, true);

	return 0;
}