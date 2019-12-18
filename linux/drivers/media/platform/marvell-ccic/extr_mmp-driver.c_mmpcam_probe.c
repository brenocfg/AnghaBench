#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; struct mmp_camera_platform_data* platform_data; } ;
struct platform_device {TYPE_3__ dev; } ;
struct mmp_camera_platform_data {int mclk_src; int mclk_div; scalar_t__ bus_type; scalar_t__* dphy; int /*<<< orphan*/  lane; } ;
struct TYPE_8__ {struct fwnode_handle* fwnode; } ;
struct TYPE_9__ {TYPE_1__ match; int /*<<< orphan*/  match_type; } ;
struct mcam_camera {int mclk_src; int mclk_div; scalar_t__ bus_type; scalar_t__* dphy; int mipi_enabled; TYPE_2__ asd; int /*<<< orphan*/  mclk; int /*<<< orphan*/  regs_size; int /*<<< orphan*/  regs; int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  buffer_mode; int /*<<< orphan*/  chip_id; TYPE_3__* dev; int /*<<< orphan*/  lane; int /*<<< orphan*/  calc_dphy; } ;
struct mmp_camera {int /*<<< orphan*/  irq; int /*<<< orphan*/  mipi_clk; struct mcam_camera mcam; int /*<<< orphan*/  devlist; struct platform_device* pdev; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_DMA_sg ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCAM_ARMADA610 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_ASYNC_MATCH_FWNODE ; 
 scalar_t__ V4L2_MBUS_CSI2_DPHY ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct mmp_camera* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mcam_camera*) ; 
 struct fwnode_handle* fwnode_graph_get_next_endpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fwnode_handle* fwnode_graph_get_remote_port_parent (struct fwnode_handle*) ; 
 int /*<<< orphan*/  fwnode_handle_put (struct fwnode_handle*) ; 
 int /*<<< orphan*/  mcam_init_clk (struct mcam_camera*) ; 
 int mccic_register (struct mcam_camera*) ; 
 int /*<<< orphan*/  mccic_shutdown (struct mcam_camera*) ; 
 int /*<<< orphan*/  mmpcam_add_device (struct mmp_camera*) ; 
 int /*<<< orphan*/  mmpcam_calc_dphy ; 
 int /*<<< orphan*/  mmpcam_irq ; 
 int of_clk_add_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_src_simple_get ; 
 int /*<<< orphan*/  of_fwnode_handle (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int mmpcam_probe(struct platform_device *pdev)
{
	struct mmp_camera *cam;
	struct mcam_camera *mcam;
	struct resource *res;
	struct fwnode_handle *ep;
	struct mmp_camera_platform_data *pdata;
	int ret;

	cam = devm_kzalloc(&pdev->dev, sizeof(*cam), GFP_KERNEL);
	if (cam == NULL)
		return -ENOMEM;
	cam->pdev = pdev;
	INIT_LIST_HEAD(&cam->devlist);

	mcam = &cam->mcam;
	mcam->calc_dphy = mmpcam_calc_dphy;
	mcam->dev = &pdev->dev;
	pdata = pdev->dev.platform_data;
	if (pdata) {
		mcam->mclk_src = pdata->mclk_src;
		mcam->mclk_div = pdata->mclk_div;
		mcam->bus_type = pdata->bus_type;
		mcam->dphy = pdata->dphy;
		mcam->lane = pdata->lane;
	} else {
		/*
		 * These are values that used to be hardcoded in mcam-core and
		 * work well on a OLPC XO 1.75 with a parallel bus sensor.
		 * If it turns out other setups make sense, the values should
		 * be obtained from the device tree.
		 */
		mcam->mclk_src = 3;
		mcam->mclk_div = 2;
	}
	if (mcam->bus_type == V4L2_MBUS_CSI2_DPHY) {
		cam->mipi_clk = devm_clk_get(mcam->dev, "mipi");
		if ((IS_ERR(cam->mipi_clk) && mcam->dphy[2] == 0))
			return PTR_ERR(cam->mipi_clk);
	}
	mcam->mipi_enabled = false;
	mcam->chip_id = MCAM_ARMADA610;
	mcam->buffer_mode = B_DMA_sg;
	strscpy(mcam->bus_info, "platform:mmp-camera", sizeof(mcam->bus_info));
	spin_lock_init(&mcam->dev_lock);
	/*
	 * Get our I/O memory.
	 */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mcam->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(mcam->regs))
		return PTR_ERR(mcam->regs);
	mcam->regs_size = resource_size(res);

	mcam_init_clk(mcam);

	/*
	 * Create a match of the sensor against its OF node.
	 */
	ep = fwnode_graph_get_next_endpoint(of_fwnode_handle(pdev->dev.of_node),
					    NULL);
	if (!ep)
		return -ENODEV;

	mcam->asd.match_type = V4L2_ASYNC_MATCH_FWNODE;
	mcam->asd.match.fwnode = fwnode_graph_get_remote_port_parent(ep);

	fwnode_handle_put(ep);

	/*
	 * Register the device with the core.
	 */
	ret = mccic_register(mcam);
	if (ret)
		return ret;

	/*
	 * Add OF clock provider.
	 */
	ret = of_clk_add_provider(pdev->dev.of_node, of_clk_src_simple_get,
								mcam->mclk);
	if (ret) {
		dev_err(&pdev->dev, "can't add DT clock provider\n");
		goto out;
	}

	/*
	 * Finally, set up our IRQ now that the core is ready to
	 * deal with it.
	 */
	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (res == NULL) {
		ret = -ENODEV;
		goto out;
	}
	cam->irq = res->start;
	ret = devm_request_irq(&pdev->dev, cam->irq, mmpcam_irq, IRQF_SHARED,
					"mmp-camera", mcam);
	if (ret == 0) {
		mmpcam_add_device(cam);
		return 0;
	}

out:
	fwnode_handle_put(mcam->asd.match.fwnode);
	mccic_shutdown(mcam);

	return ret;
}