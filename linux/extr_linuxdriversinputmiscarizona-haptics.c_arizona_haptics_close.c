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
struct snd_soc_component {int dummy; } ;
struct input_dev {int dummy; } ;
struct arizona_haptics {TYPE_1__* arizona; int /*<<< orphan*/  work; } ;
struct TYPE_2__ {scalar_t__ dapm; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct arizona_haptics* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  snd_soc_component_disable_pin (struct snd_soc_component*,char*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (scalar_t__) ; 

__attribute__((used)) static void arizona_haptics_close(struct input_dev *input)
{
	struct arizona_haptics *haptics = input_get_drvdata(input);
	struct snd_soc_component *component;

	cancel_work_sync(&haptics->work);

	if (haptics->arizona->dapm) {
		component = snd_soc_dapm_to_component(haptics->arizona->dapm);
		snd_soc_component_disable_pin(component, "HAPTICS");
	}
}