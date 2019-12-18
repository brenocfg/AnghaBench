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
struct platform_device {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_SND ; 
 int /*<<< orphan*/  SND_BELL ; 
 int /*<<< orphan*/  input_unregister_device (struct input_dev*) ; 
 int /*<<< orphan*/  pcspkr_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct input_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int pcspkr_remove(struct platform_device *dev)
{
	struct input_dev *pcspkr_dev = platform_get_drvdata(dev);

	input_unregister_device(pcspkr_dev);
	/* turn off the speaker */
	pcspkr_event(NULL, EV_SND, SND_BELL, 0);

	return 0;
}