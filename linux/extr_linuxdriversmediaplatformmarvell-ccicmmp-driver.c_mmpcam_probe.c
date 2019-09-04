#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_7__ {struct mmp_camera_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  id; } ;
struct mmp_camera_platform_data {scalar_t__ bus_type; scalar_t__* dphy; int /*<<< orphan*/  sensor_reset_gpio; int /*<<< orphan*/  sensor_power_gpio; int /*<<< orphan*/  i2c_device; int /*<<< orphan*/  lane; int /*<<< orphan*/  mclk_div; int /*<<< orphan*/  mclk_src; int /*<<< orphan*/  mclk_min; } ;
struct mcam_camera {int (* plat_power_up ) (struct mcam_camera*) ;scalar_t__ bus_type; scalar_t__* dphy; int mipi_enabled; int /*<<< orphan*/ * i2c_adapter; int /*<<< orphan*/  regs_size; void* regs; int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  buffer_mode; int /*<<< orphan*/  chip_id; int /*<<< orphan*/  lane; TYPE_1__* dev; int /*<<< orphan*/  mclk_div; int /*<<< orphan*/  mclk_src; int /*<<< orphan*/  mclk_min; int /*<<< orphan*/  ccic_id; scalar_t__ use_smbus; int /*<<< orphan*/  calc_dphy; int /*<<< orphan*/  ctlr_reset; int /*<<< orphan*/  (* plat_power_down ) (struct mcam_camera*) ;} ;
struct mmp_camera {int /*<<< orphan*/  irq; void* power_regs; void* mipi_clk; struct mcam_camera mcam; int /*<<< orphan*/  devlist; struct platform_device* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_DMA_sg ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MCAM_ARMADA610 ; 
 int PTR_ERR (void*) ; 
 scalar_t__ V4L2_MBUS_CSI2 ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 int devm_gpio_request (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 void* devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct mmp_camera* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mcam_camera*) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcam_ctlr_reset ; 
 int /*<<< orphan*/  mcam_init_clk (struct mcam_camera*) ; 
 int mccic_register (struct mcam_camera*) ; 
 int /*<<< orphan*/  mccic_shutdown (struct mcam_camera*) ; 
 int /*<<< orphan*/  mmpcam_add_device (struct mmp_camera*) ; 
 int /*<<< orphan*/  mmpcam_calc_dphy ; 
 int /*<<< orphan*/  mmpcam_irq ; 
 int /*<<< orphan*/  mmpcam_power_down (struct mcam_camera*) ; 
 int mmpcam_power_up (struct mcam_camera*) ; 
 int /*<<< orphan*/ * platform_get_drvdata (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int mmpcam_probe(struct platform_device *pdev)
{
	struct mmp_camera *cam;
	struct mcam_camera *mcam;
	struct resource *res;
	struct mmp_camera_platform_data *pdata;
	int ret;

	pdata = pdev->dev.platform_data;
	if (!pdata)
		return -ENODEV;

	cam = devm_kzalloc(&pdev->dev, sizeof(*cam), GFP_KERNEL);
	if (cam == NULL)
		return -ENOMEM;
	cam->pdev = pdev;
	INIT_LIST_HEAD(&cam->devlist);

	mcam = &cam->mcam;
	mcam->plat_power_up = mmpcam_power_up;
	mcam->plat_power_down = mmpcam_power_down;
	mcam->ctlr_reset = mcam_ctlr_reset;
	mcam->calc_dphy = mmpcam_calc_dphy;
	mcam->dev = &pdev->dev;
	mcam->use_smbus = 0;
	mcam->ccic_id = pdev->id;
	mcam->mclk_min = pdata->mclk_min;
	mcam->mclk_src = pdata->mclk_src;
	mcam->mclk_div = pdata->mclk_div;
	mcam->bus_type = pdata->bus_type;
	mcam->dphy = pdata->dphy;
	if (mcam->bus_type == V4L2_MBUS_CSI2) {
		cam->mipi_clk = devm_clk_get(mcam->dev, "mipi");
		if ((IS_ERR(cam->mipi_clk) && mcam->dphy[2] == 0))
			return PTR_ERR(cam->mipi_clk);
	}
	mcam->mipi_enabled = false;
	mcam->lane = pdata->lane;
	mcam->chip_id = MCAM_ARMADA610;
	mcam->buffer_mode = B_DMA_sg;
	strlcpy(mcam->bus_info, "platform:mmp-camera", sizeof(mcam->bus_info));
	spin_lock_init(&mcam->dev_lock);
	/*
	 * Get our I/O memory.
	 */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mcam->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(mcam->regs))
		return PTR_ERR(mcam->regs);
	mcam->regs_size = resource_size(res);
	/*
	 * Power/clock memory is elsewhere; get it too.  Perhaps this
	 * should really be managed outside of this driver?
	 */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	cam->power_regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(cam->power_regs))
		return PTR_ERR(cam->power_regs);
	/*
	 * Find the i2c adapter.  This assumes, of course, that the
	 * i2c bus is already up and functioning.
	 */
	mcam->i2c_adapter = platform_get_drvdata(pdata->i2c_device);
	if (mcam->i2c_adapter == NULL) {
		dev_err(&pdev->dev, "No i2c adapter\n");
		return -ENODEV;
	}
	/*
	 * Sensor GPIO pins.
	 */
	ret = devm_gpio_request(&pdev->dev, pdata->sensor_power_gpio,
							"cam-power");
	if (ret) {
		dev_err(&pdev->dev, "Can't get sensor power gpio %d",
				pdata->sensor_power_gpio);
		return ret;
	}
	gpio_direction_output(pdata->sensor_power_gpio, 0);
	ret = devm_gpio_request(&pdev->dev, pdata->sensor_reset_gpio,
							"cam-reset");
	if (ret) {
		dev_err(&pdev->dev, "Can't get sensor reset gpio %d",
				pdata->sensor_reset_gpio);
		return ret;
	}
	gpio_direction_output(pdata->sensor_reset_gpio, 0);

	mcam_init_clk(mcam);

	/*
	 * Power the device up and hand it off to the core.
	 */
	ret = mmpcam_power_up(mcam);
	if (ret)
		return ret;
	ret = mccic_register(mcam);
	if (ret)
		goto out_power_down;
	/*
	 * Finally, set up our IRQ now that the core is ready to
	 * deal with it.
	 */
	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (res == NULL) {
		ret = -ENODEV;
		goto out_unregister;
	}
	cam->irq = res->start;
	ret = devm_request_irq(&pdev->dev, cam->irq, mmpcam_irq, IRQF_SHARED,
					"mmp-camera", mcam);
	if (ret == 0) {
		mmpcam_add_device(cam);
		return 0;
	}

out_unregister:
	mccic_shutdown(mcam);
out_power_down:
	mmpcam_power_down(mcam);
	return ret;
}