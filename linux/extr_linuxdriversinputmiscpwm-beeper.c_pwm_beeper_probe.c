#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pwm_state {int enabled; } ;
struct pwm_beeper {int bell_frequency; TYPE_2__* input; int /*<<< orphan*/  work; int /*<<< orphan*/  amplifier; int /*<<< orphan*/  pwm; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_6__ {int vendor; int product; int version; int /*<<< orphan*/  bustype; } ;
struct TYPE_7__ {char* name; char* phys; int /*<<< orphan*/  close; int /*<<< orphan*/  event; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  EV_SND ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_BELL ; 
 int /*<<< orphan*/  SND_TONE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int device_property_read_u32 (struct device*,char*,int*) ; 
 TYPE_2__* devm_input_allocate_device (struct device*) ; 
 struct pwm_beeper* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pwm_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regulator_get (struct device*,char*) ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_2__*,struct pwm_beeper*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pwm_beeper*) ; 
 int pwm_apply_state (int /*<<< orphan*/ ,struct pwm_state*) ; 
 int /*<<< orphan*/  pwm_beeper_close ; 
 int /*<<< orphan*/  pwm_beeper_event ; 
 int /*<<< orphan*/  pwm_beeper_work ; 
 int /*<<< orphan*/  pwm_init_state (int /*<<< orphan*/ ,struct pwm_state*) ; 

__attribute__((used)) static int pwm_beeper_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct pwm_beeper *beeper;
	struct pwm_state state;
	u32 bell_frequency;
	int error;

	beeper = devm_kzalloc(dev, sizeof(*beeper), GFP_KERNEL);
	if (!beeper)
		return -ENOMEM;

	beeper->pwm = devm_pwm_get(dev, NULL);
	if (IS_ERR(beeper->pwm)) {
		error = PTR_ERR(beeper->pwm);
		if (error != -EPROBE_DEFER)
			dev_err(dev, "Failed to request PWM device: %d\n",
				error);
		return error;
	}

	/* Sync up PWM state and ensure it is off. */
	pwm_init_state(beeper->pwm, &state);
	state.enabled = false;
	error = pwm_apply_state(beeper->pwm, &state);
	if (error) {
		dev_err(dev, "failed to apply initial PWM state: %d\n",
			error);
		return error;
	}

	beeper->amplifier = devm_regulator_get(dev, "amp");
	if (IS_ERR(beeper->amplifier)) {
		error = PTR_ERR(beeper->amplifier);
		if (error != -EPROBE_DEFER)
			dev_err(dev, "Failed to get 'amp' regulator: %d\n",
				error);
		return error;
	}

	INIT_WORK(&beeper->work, pwm_beeper_work);

	error = device_property_read_u32(dev, "beeper-hz", &bell_frequency);
	if (error) {
		bell_frequency = 1000;
		dev_dbg(dev,
			"failed to parse 'beeper-hz' property, using default: %uHz\n",
			bell_frequency);
	}

	beeper->bell_frequency = bell_frequency;

	beeper->input = devm_input_allocate_device(dev);
	if (!beeper->input) {
		dev_err(dev, "Failed to allocate input device\n");
		return -ENOMEM;
	}

	beeper->input->name = "pwm-beeper";
	beeper->input->phys = "pwm/input0";
	beeper->input->id.bustype = BUS_HOST;
	beeper->input->id.vendor = 0x001f;
	beeper->input->id.product = 0x0001;
	beeper->input->id.version = 0x0100;

	input_set_capability(beeper->input, EV_SND, SND_TONE);
	input_set_capability(beeper->input, EV_SND, SND_BELL);

	beeper->input->event = pwm_beeper_event;
	beeper->input->close = pwm_beeper_close;

	input_set_drvdata(beeper->input, beeper);

	error = input_register_device(beeper->input);
	if (error) {
		dev_err(dev, "Failed to register input device: %d\n", error);
		return error;
	}

	platform_set_drvdata(pdev, beeper);

	return 0;
}