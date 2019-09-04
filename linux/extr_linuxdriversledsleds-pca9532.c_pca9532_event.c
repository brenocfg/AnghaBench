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
struct pca9532_data {int* pwm; int /*<<< orphan*/  work; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 unsigned int EV_SND ; 
 unsigned int SND_BELL ; 
 unsigned int SND_TONE ; 
 struct pca9532_data* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pca9532_event(struct input_dev *dev, unsigned int type,
	unsigned int code, int value)
{
	struct pca9532_data *data = input_get_drvdata(dev);

	if (!(type == EV_SND && (code == SND_BELL || code == SND_TONE)))
		return -1;

	/* XXX: allow different kind of beeps with psc/pwm modifications */
	if (value > 1 && value < 32767)
		data->pwm[1] = 127;
	else
		data->pwm[1] = 0;

	schedule_work(&data->work);

	return 0;
}