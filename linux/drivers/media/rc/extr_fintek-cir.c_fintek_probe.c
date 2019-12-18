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
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct rc_dev {char* input_phys; void* rx_resolution; void* timeout; int /*<<< orphan*/  map_name; int /*<<< orphan*/  driver_name; TYPE_2__ dev; TYPE_1__ input_id; int /*<<< orphan*/  device_name; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  allowed_protocols; struct fintek_dev* priv; } ;
struct pnp_device_id {int dummy; } ;
struct pnp_dev {int /*<<< orphan*/  dev; } ;
struct fintek_dev {int /*<<< orphan*/  cir_port_len; int /*<<< orphan*/  cir_addr; int /*<<< orphan*/  cir_irq; struct rc_dev* rdev; int /*<<< orphan*/  chip_minor; int /*<<< orphan*/  chip_major; struct pnp_dev* pdev; int /*<<< orphan*/  fintek_lock; int /*<<< orphan*/  cr_dp; int /*<<< orphan*/  cr_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int CIR_SAMPLE_PERIOD ; 
 int /*<<< orphan*/  CR_DATA_PORT ; 
 int /*<<< orphan*/  CR_INDEX_PORT ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FINTEK_DESCRIPTION ; 
 int /*<<< orphan*/  FINTEK_DRIVER_NAME ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  RC_DRIVER_IR_RAW ; 
 int /*<<< orphan*/  RC_MAP_RC6_MCE ; 
 int /*<<< orphan*/  RC_PROTO_BIT_ALL_IR_DECODER ; 
 void* US_TO_NS (int) ; 
 int /*<<< orphan*/  VENDOR_ID_FINTEK ; 
 int /*<<< orphan*/  cir_dump_regs (struct fintek_dev*) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fintek_cir_isr ; 
 int /*<<< orphan*/  fintek_cir_ldev_init (struct fintek_dev*) ; 
 int /*<<< orphan*/  fintek_cir_regs_init (struct fintek_dev*) ; 
 int /*<<< orphan*/  fintek_close ; 
 int /*<<< orphan*/  fintek_config_mode_disable (struct fintek_dev*) ; 
 int /*<<< orphan*/  fintek_config_mode_enable (struct fintek_dev*) ; 
 int fintek_hw_detect (struct fintek_dev*) ; 
 int /*<<< orphan*/  fintek_open ; 
 int /*<<< orphan*/  fit_pr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fintek_dev*) ; 
 int /*<<< orphan*/  kfree (struct fintek_dev*) ; 
 struct fintek_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_irq (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_irq_valid (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_port_len (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_port_start (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_port_valid (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_set_drvdata (struct pnp_dev*,struct fintek_dev*) ; 
 struct rc_dev* rc_allocate_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  request_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fintek_probe(struct pnp_dev *pdev, const struct pnp_device_id *dev_id)
{
	struct fintek_dev *fintek;
	struct rc_dev *rdev;
	int ret = -ENOMEM;

	fintek = kzalloc(sizeof(struct fintek_dev), GFP_KERNEL);
	if (!fintek)
		return ret;

	/* input device for IR remote (and tx) */
	rdev = rc_allocate_device(RC_DRIVER_IR_RAW);
	if (!rdev)
		goto exit_free_dev_rdev;

	ret = -ENODEV;
	/* validate pnp resources */
	if (!pnp_port_valid(pdev, 0)) {
		dev_err(&pdev->dev, "IR PNP Port not valid!\n");
		goto exit_free_dev_rdev;
	}

	if (!pnp_irq_valid(pdev, 0)) {
		dev_err(&pdev->dev, "IR PNP IRQ not valid!\n");
		goto exit_free_dev_rdev;
	}

	fintek->cir_addr = pnp_port_start(pdev, 0);
	fintek->cir_irq  = pnp_irq(pdev, 0);
	fintek->cir_port_len = pnp_port_len(pdev, 0);

	fintek->cr_ip = CR_INDEX_PORT;
	fintek->cr_dp = CR_DATA_PORT;

	spin_lock_init(&fintek->fintek_lock);

	pnp_set_drvdata(pdev, fintek);
	fintek->pdev = pdev;

	ret = fintek_hw_detect(fintek);
	if (ret)
		goto exit_free_dev_rdev;

	/* Initialize CIR & CIR Wake Logical Devices */
	fintek_config_mode_enable(fintek);
	fintek_cir_ldev_init(fintek);
	fintek_config_mode_disable(fintek);

	/* Initialize CIR & CIR Wake Config Registers */
	fintek_cir_regs_init(fintek);

	/* Set up the rc device */
	rdev->priv = fintek;
	rdev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rdev->open = fintek_open;
	rdev->close = fintek_close;
	rdev->device_name = FINTEK_DESCRIPTION;
	rdev->input_phys = "fintek/cir0";
	rdev->input_id.bustype = BUS_HOST;
	rdev->input_id.vendor = VENDOR_ID_FINTEK;
	rdev->input_id.product = fintek->chip_major;
	rdev->input_id.version = fintek->chip_minor;
	rdev->dev.parent = &pdev->dev;
	rdev->driver_name = FINTEK_DRIVER_NAME;
	rdev->map_name = RC_MAP_RC6_MCE;
	rdev->timeout = US_TO_NS(1000);
	/* rx resolution is hardwired to 50us atm, 1, 25, 100 also possible */
	rdev->rx_resolution = US_TO_NS(CIR_SAMPLE_PERIOD);

	fintek->rdev = rdev;

	ret = -EBUSY;
	/* now claim resources */
	if (!request_region(fintek->cir_addr,
			    fintek->cir_port_len, FINTEK_DRIVER_NAME))
		goto exit_free_dev_rdev;

	if (request_irq(fintek->cir_irq, fintek_cir_isr, IRQF_SHARED,
			FINTEK_DRIVER_NAME, (void *)fintek))
		goto exit_free_cir_addr;

	ret = rc_register_device(rdev);
	if (ret)
		goto exit_free_irq;

	device_init_wakeup(&pdev->dev, true);

	fit_pr(KERN_NOTICE, "driver has been successfully loaded\n");
	if (debug)
		cir_dump_regs(fintek);

	return 0;

exit_free_irq:
	free_irq(fintek->cir_irq, fintek);
exit_free_cir_addr:
	release_region(fintek->cir_addr, fintek->cir_port_len);
exit_free_dev_rdev:
	rc_free_device(rdev);
	kfree(fintek);

	return ret;
}