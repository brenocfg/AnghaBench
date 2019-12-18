#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct pmic8xxx_kp {unsigned int num_rows; unsigned int num_cols; scalar_t__ key_sense_irq; scalar_t__ key_stuck_irq; unsigned int ctrl_reg; TYPE_3__* input; int /*<<< orphan*/  regmap; int /*<<< orphan*/  stuckstate; int /*<<< orphan*/  keystate; int /*<<< orphan*/  keycodes; TYPE_2__* dev; } ;
struct TYPE_14__ {int /*<<< orphan*/  parent; struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_13__ {int version; int product; int vendor; int /*<<< orphan*/  bustype; } ;
struct TYPE_15__ {char* name; char* phys; int /*<<< orphan*/  evbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_I2C ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  KEYP_CTRL ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 unsigned int PM8XXX_MAX_COLS ; 
 unsigned int PM8XXX_MAX_ROWS ; 
 unsigned int PM8XXX_MIN_COLS ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_2__*,int) ; 
 TYPE_3__* devm_input_allocate_device (TYPE_2__*) ; 
 struct pmic8xxx_kp* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_any_context_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pmic8xxx_kp*) ; 
 int input_register_device (TYPE_3__*) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_3__*,struct pmic8xxx_kp*) ; 
 int matrix_keypad_build_keymap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int matrix_keypad_parse_properties (TYPE_2__*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pmic8xxx_kp*) ; 
 int /*<<< orphan*/  pmic8xxx_kp_close ; 
 int /*<<< orphan*/  pmic8xxx_kp_irq ; 
 int /*<<< orphan*/  pmic8xxx_kp_open ; 
 int /*<<< orphan*/  pmic8xxx_kp_stuck_irq ; 
 int pmic8xxx_kpd_init (struct pmic8xxx_kp*,struct platform_device*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int pmic8xxx_kp_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	unsigned int rows, cols;
	bool repeat;
	bool wakeup;
	struct pmic8xxx_kp *kp;
	int rc;
	unsigned int ctrl_val;

	rc = matrix_keypad_parse_properties(&pdev->dev, &rows, &cols);
	if (rc)
		return rc;

	if (cols > PM8XXX_MAX_COLS || rows > PM8XXX_MAX_ROWS ||
	    cols < PM8XXX_MIN_COLS) {
		dev_err(&pdev->dev, "invalid platform data\n");
		return -EINVAL;
	}

	repeat = !of_property_read_bool(np, "linux,input-no-autorepeat");

	wakeup = of_property_read_bool(np, "wakeup-source") ||
		 /* legacy name */
		 of_property_read_bool(np, "linux,keypad-wakeup");

	kp = devm_kzalloc(&pdev->dev, sizeof(*kp), GFP_KERNEL);
	if (!kp)
		return -ENOMEM;

	kp->regmap = dev_get_regmap(pdev->dev.parent, NULL);
	if (!kp->regmap)
		return -ENODEV;

	platform_set_drvdata(pdev, kp);

	kp->num_rows	= rows;
	kp->num_cols	= cols;
	kp->dev		= &pdev->dev;

	kp->input = devm_input_allocate_device(&pdev->dev);
	if (!kp->input) {
		dev_err(&pdev->dev, "unable to allocate input device\n");
		return -ENOMEM;
	}

	kp->key_sense_irq = platform_get_irq(pdev, 0);
	if (kp->key_sense_irq < 0)
		return kp->key_sense_irq;

	kp->key_stuck_irq = platform_get_irq(pdev, 1);
	if (kp->key_stuck_irq < 0)
		return kp->key_stuck_irq;

	kp->input->name = "PMIC8XXX keypad";
	kp->input->phys = "pmic8xxx_keypad/input0";

	kp->input->id.bustype	= BUS_I2C;
	kp->input->id.version	= 0x0001;
	kp->input->id.product	= 0x0001;
	kp->input->id.vendor	= 0x0001;

	kp->input->open		= pmic8xxx_kp_open;
	kp->input->close	= pmic8xxx_kp_close;

	rc = matrix_keypad_build_keymap(NULL, NULL,
					PM8XXX_MAX_ROWS, PM8XXX_MAX_COLS,
					kp->keycodes, kp->input);
	if (rc) {
		dev_err(&pdev->dev, "failed to build keymap\n");
		return rc;
	}

	if (repeat)
		__set_bit(EV_REP, kp->input->evbit);
	input_set_capability(kp->input, EV_MSC, MSC_SCAN);

	input_set_drvdata(kp->input, kp);

	/* initialize keypad state */
	memset(kp->keystate, 0xff, sizeof(kp->keystate));
	memset(kp->stuckstate, 0xff, sizeof(kp->stuckstate));

	rc = pmic8xxx_kpd_init(kp, pdev);
	if (rc < 0) {
		dev_err(&pdev->dev, "unable to initialize keypad controller\n");
		return rc;
	}

	rc = devm_request_any_context_irq(&pdev->dev, kp->key_sense_irq,
			pmic8xxx_kp_irq, IRQF_TRIGGER_RISING, "pmic-keypad",
			kp);
	if (rc < 0) {
		dev_err(&pdev->dev, "failed to request keypad sense irq\n");
		return rc;
	}

	rc = devm_request_any_context_irq(&pdev->dev, kp->key_stuck_irq,
			pmic8xxx_kp_stuck_irq, IRQF_TRIGGER_RISING,
			"pmic-keypad-stuck", kp);
	if (rc < 0) {
		dev_err(&pdev->dev, "failed to request keypad stuck irq\n");
		return rc;
	}

	rc = regmap_read(kp->regmap, KEYP_CTRL, &ctrl_val);
	if (rc < 0) {
		dev_err(&pdev->dev, "failed to read KEYP_CTRL register\n");
		return rc;
	}

	kp->ctrl_reg = ctrl_val;

	rc = input_register_device(kp->input);
	if (rc < 0) {
		dev_err(&pdev->dev, "unable to register keypad input device\n");
		return rc;
	}

	device_init_wakeup(&pdev->dev, wakeup);

	return 0;
}