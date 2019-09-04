#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int bits_per_word; int /*<<< orphan*/  dev; TYPE_2__* master; int /*<<< orphan*/  mode; } ;
struct psxpad {int /*<<< orphan*/  phys; struct spi_device* spi; struct input_polled_dev* pdev; } ;
struct input_polled_dev {int poll_interval; int poll_interval_min; int poll_interval_max; struct input_dev* input; int /*<<< orphan*/  poll; int /*<<< orphan*/  close; int /*<<< orphan*/  open; struct psxpad* private; } ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; TYPE_1__ id; } ;
struct TYPE_4__ {int min_speed_hz; int max_speed_hz; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_RX ; 
 int /*<<< orphan*/  ABS_RY ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_A ; 
 int /*<<< orphan*/  BTN_B ; 
 int /*<<< orphan*/  BTN_DPAD_DOWN ; 
 int /*<<< orphan*/  BTN_DPAD_LEFT ; 
 int /*<<< orphan*/  BTN_DPAD_RIGHT ; 
 int /*<<< orphan*/  BTN_DPAD_UP ; 
 int /*<<< orphan*/  BTN_SELECT ; 
 int /*<<< orphan*/  BTN_START ; 
 int /*<<< orphan*/  BTN_THUMBL ; 
 int /*<<< orphan*/  BTN_THUMBR ; 
 int /*<<< orphan*/  BTN_TL ; 
 int /*<<< orphan*/  BTN_TL2 ; 
 int /*<<< orphan*/  BTN_TR ; 
 int /*<<< orphan*/  BTN_TR2 ; 
 int /*<<< orphan*/  BTN_X ; 
 int /*<<< orphan*/  BTN_Y ; 
 int /*<<< orphan*/  BUS_SPI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SPI_MODE_3 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 struct psxpad* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct input_polled_dev* input_allocate_polled_device () ; 
 int input_register_polled_device (struct input_polled_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psxpad_set_motor_level (struct psxpad*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int psxpad_spi_init_ff (struct psxpad*) ; 
 int /*<<< orphan*/  psxpad_spi_poll ; 
 int /*<<< orphan*/  psxpad_spi_poll_close ; 
 int /*<<< orphan*/  psxpad_spi_poll_open ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  spi_setup (struct spi_device*) ; 

__attribute__((used)) static int psxpad_spi_probe(struct spi_device *spi)
{
	struct psxpad *pad;
	struct input_polled_dev *pdev;
	struct input_dev *idev;
	int err;

	pad = devm_kzalloc(&spi->dev, sizeof(struct psxpad), GFP_KERNEL);
	if (!pad)
		return -ENOMEM;

	pdev = input_allocate_polled_device();
	if (!pdev) {
		dev_err(&spi->dev, "failed to allocate input device\n");
		return -ENOMEM;
	}

	/* input poll device settings */
	pad->pdev = pdev;
	pad->spi = spi;

	pdev->private = pad;
	pdev->open = psxpad_spi_poll_open;
	pdev->close = psxpad_spi_poll_close;
	pdev->poll = psxpad_spi_poll;
	/* poll interval is about 60fps */
	pdev->poll_interval = 16;
	pdev->poll_interval_min = 8;
	pdev->poll_interval_max = 32;

	/* input device settings */
	idev = pdev->input;
	idev->name = "PlayStation 1/2 joypad";
	snprintf(pad->phys, sizeof(pad->phys), "%s/input", dev_name(&spi->dev));
	idev->id.bustype = BUS_SPI;

	/* key/value map settings */
	input_set_abs_params(idev, ABS_X, 0, 255, 0, 0);
	input_set_abs_params(idev, ABS_Y, 0, 255, 0, 0);
	input_set_abs_params(idev, ABS_RX, 0, 255, 0, 0);
	input_set_abs_params(idev, ABS_RY, 0, 255, 0, 0);
	input_set_capability(idev, EV_KEY, BTN_DPAD_UP);
	input_set_capability(idev, EV_KEY, BTN_DPAD_DOWN);
	input_set_capability(idev, EV_KEY, BTN_DPAD_LEFT);
	input_set_capability(idev, EV_KEY, BTN_DPAD_RIGHT);
	input_set_capability(idev, EV_KEY, BTN_A);
	input_set_capability(idev, EV_KEY, BTN_B);
	input_set_capability(idev, EV_KEY, BTN_X);
	input_set_capability(idev, EV_KEY, BTN_Y);
	input_set_capability(idev, EV_KEY, BTN_TL);
	input_set_capability(idev, EV_KEY, BTN_TR);
	input_set_capability(idev, EV_KEY, BTN_TL2);
	input_set_capability(idev, EV_KEY, BTN_TR2);
	input_set_capability(idev, EV_KEY, BTN_THUMBL);
	input_set_capability(idev, EV_KEY, BTN_THUMBR);
	input_set_capability(idev, EV_KEY, BTN_SELECT);
	input_set_capability(idev, EV_KEY, BTN_START);

	err = psxpad_spi_init_ff(pad);
	if (err)
		return err;

	/* SPI settings */
	spi->mode = SPI_MODE_3;
	spi->bits_per_word = 8;
	/* (PlayStation 1/2 joypad might be possible works 250kHz/500kHz) */
	spi->master->min_speed_hz = 125000;
	spi->master->max_speed_hz = 125000;
	spi_setup(spi);

	/* pad settings */
	psxpad_set_motor_level(pad, 0, 0);

	/* register input poll device */
	err = input_register_polled_device(pdev);
	if (err) {
		dev_err(&spi->dev,
			"failed to register input poll device: %d\n", err);
		return err;
	}

	pm_runtime_enable(&spi->dev);

	return 0;
}