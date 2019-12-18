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
struct virtio_net_config {int /*<<< orphan*/  mac; int /*<<< orphan*/  status; int /*<<< orphan*/  mtu; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct mlxbf_tmfifo {int is_ready; int /*<<< orphan*/  timer; TYPE_1__* irq_info; void* tx_base; void* rx_base; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; int /*<<< orphan*/  spin_lock; } ;
typedef  int /*<<< orphan*/  net_config ;
struct TYPE_2__ {int index; scalar_t__ irq; struct mlxbf_tmfifo* fifo; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_DATA_LEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MLXBF_TMFIFO_NET_FEATURES ; 
 scalar_t__ MLXBF_TMFIFO_TIMER_INTERVAL ; 
 int MLXBF_TM_MAX_IRQ ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  VIRTIO_ID_CONSOLE ; 
 int /*<<< orphan*/  VIRTIO_ID_NET ; 
 int /*<<< orphan*/  VIRTIO_NET_S_LINK_UP ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct mlxbf_tmfifo* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_platform_ioremap_resource (struct platform_device*,int) ; 
 int devm_request_irq (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memset (struct virtio_net_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxbf_tmfifo_cleanup (struct mlxbf_tmfifo*) ; 
 int mlxbf_tmfifo_create_vdev (struct device*,struct mlxbf_tmfifo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct virtio_net_config*,int) ; 
 int /*<<< orphan*/  mlxbf_tmfifo_get_cfg_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxbf_tmfifo_irq_handler ; 
 int /*<<< orphan*/  mlxbf_tmfifo_set_threshold (struct mlxbf_tmfifo*) ; 
 int /*<<< orphan*/  mlxbf_tmfifo_timer ; 
 int /*<<< orphan*/  mlxbf_tmfifo_work_handler ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mlxbf_tmfifo*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxbf_tmfifo_probe(struct platform_device *pdev)
{
	struct virtio_net_config net_config;
	struct device *dev = &pdev->dev;
	struct mlxbf_tmfifo *fifo;
	int i, rc;

	fifo = devm_kzalloc(dev, sizeof(*fifo), GFP_KERNEL);
	if (!fifo)
		return -ENOMEM;

	spin_lock_init(&fifo->spin_lock);
	INIT_WORK(&fifo->work, mlxbf_tmfifo_work_handler);
	mutex_init(&fifo->lock);

	/* Get the resource of the Rx FIFO. */
	fifo->rx_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(fifo->rx_base))
		return PTR_ERR(fifo->rx_base);

	/* Get the resource of the Tx FIFO. */
	fifo->tx_base = devm_platform_ioremap_resource(pdev, 1);
	if (IS_ERR(fifo->tx_base))
		return PTR_ERR(fifo->tx_base);

	platform_set_drvdata(pdev, fifo);

	timer_setup(&fifo->timer, mlxbf_tmfifo_timer, 0);

	for (i = 0; i < MLXBF_TM_MAX_IRQ; i++) {
		fifo->irq_info[i].index = i;
		fifo->irq_info[i].fifo = fifo;
		fifo->irq_info[i].irq = platform_get_irq(pdev, i);
		rc = devm_request_irq(dev, fifo->irq_info[i].irq,
				      mlxbf_tmfifo_irq_handler, 0,
				      "tmfifo", &fifo->irq_info[i]);
		if (rc) {
			dev_err(dev, "devm_request_irq failed\n");
			fifo->irq_info[i].irq = 0;
			return rc;
		}
	}

	mlxbf_tmfifo_set_threshold(fifo);

	/* Create the console vdev. */
	rc = mlxbf_tmfifo_create_vdev(dev, fifo, VIRTIO_ID_CONSOLE, 0, NULL, 0);
	if (rc)
		goto fail;

	/* Create the network vdev. */
	memset(&net_config, 0, sizeof(net_config));
	net_config.mtu = ETH_DATA_LEN;
	net_config.status = VIRTIO_NET_S_LINK_UP;
	mlxbf_tmfifo_get_cfg_mac(net_config.mac);
	rc = mlxbf_tmfifo_create_vdev(dev, fifo, VIRTIO_ID_NET,
				      MLXBF_TMFIFO_NET_FEATURES, &net_config,
				      sizeof(net_config));
	if (rc)
		goto fail;

	mod_timer(&fifo->timer, jiffies + MLXBF_TMFIFO_TIMER_INTERVAL);

	fifo->is_ready = true;
	return 0;

fail:
	mlxbf_tmfifo_cleanup(fifo);
	return rc;
}