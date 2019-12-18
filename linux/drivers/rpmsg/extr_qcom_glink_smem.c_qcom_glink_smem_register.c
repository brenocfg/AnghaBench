#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
typedef  scalar_t__ qcom_glink ;
struct TYPE_3__ {size_t length; int /*<<< orphan*/  write; int /*<<< orphan*/  avail; int /*<<< orphan*/  advance; int /*<<< orphan*/  peak; } ;
struct glink_smem_pipe {TYPE_1__ native; scalar_t__* head; scalar_t__* tail; void* remote_pid; scalar_t__* fifo; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; struct device* parent; int /*<<< orphan*/  release; } ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GLINK_FEATURE_INTENT_REUSE ; 
 scalar_t__ IS_ERR (scalar_t__*) ; 
 int PTR_ERR (scalar_t__*) ; 
 int /*<<< orphan*/  SMEM_GLINK_NATIVE_XPRT_DESCRIPTOR ; 
 int /*<<< orphan*/  SMEM_GLINK_NATIVE_XPRT_FIFO_0 ; 
 int SZ_16K ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ,struct device_node*) ; 
 int device_register (struct device*) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 struct glink_smem_pipe* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glink_smem_rx_advance ; 
 int /*<<< orphan*/  glink_smem_rx_avail ; 
 int /*<<< orphan*/  glink_smem_rx_peak ; 
 int /*<<< orphan*/  glink_smem_tx_avail ; 
 int /*<<< orphan*/  glink_smem_tx_write ; 
 struct device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,void**) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 scalar_t__* qcom_glink_native_probe (struct device*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  qcom_glink_smem_release ; 
 int qcom_smem_alloc (void*,int /*<<< orphan*/ ,int) ; 
 void* qcom_smem_get (void*,int /*<<< orphan*/ ,size_t*) ; 

struct qcom_glink *qcom_glink_smem_register(struct device *parent,
					    struct device_node *node)
{
	struct glink_smem_pipe *rx_pipe;
	struct glink_smem_pipe *tx_pipe;
	struct qcom_glink *glink;
	struct device *dev;
	u32 remote_pid;
	__le32 *descs;
	size_t size;
	int ret;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return ERR_PTR(-ENOMEM);

	dev->parent = parent;
	dev->of_node = node;
	dev->release = qcom_glink_smem_release;
	dev_set_name(dev, "%s:%pOFn", dev_name(parent->parent), node);
	ret = device_register(dev);
	if (ret) {
		pr_err("failed to register glink edge\n");
		put_device(dev);
		return ERR_PTR(ret);
	}

	ret = of_property_read_u32(dev->of_node, "qcom,remote-pid",
				   &remote_pid);
	if (ret) {
		dev_err(dev, "failed to parse qcom,remote-pid\n");
		goto err_put_dev;
	}

	rx_pipe = devm_kzalloc(dev, sizeof(*rx_pipe), GFP_KERNEL);
	tx_pipe = devm_kzalloc(dev, sizeof(*tx_pipe), GFP_KERNEL);
	if (!rx_pipe || !tx_pipe) {
		ret = -ENOMEM;
		goto err_put_dev;
	}

	ret = qcom_smem_alloc(remote_pid,
			      SMEM_GLINK_NATIVE_XPRT_DESCRIPTOR, 32);
	if (ret && ret != -EEXIST) {
		dev_err(dev, "failed to allocate glink descriptors\n");
		goto err_put_dev;
	}

	descs = qcom_smem_get(remote_pid,
			      SMEM_GLINK_NATIVE_XPRT_DESCRIPTOR, &size);
	if (IS_ERR(descs)) {
		dev_err(dev, "failed to acquire xprt descriptor\n");
		ret = PTR_ERR(descs);
		goto err_put_dev;
	}

	if (size != 32) {
		dev_err(dev, "glink descriptor of invalid size\n");
		ret = -EINVAL;
		goto err_put_dev;
	}

	tx_pipe->tail = &descs[0];
	tx_pipe->head = &descs[1];
	rx_pipe->tail = &descs[2];
	rx_pipe->head = &descs[3];

	ret = qcom_smem_alloc(remote_pid, SMEM_GLINK_NATIVE_XPRT_FIFO_0,
			      SZ_16K);
	if (ret && ret != -EEXIST) {
		dev_err(dev, "failed to allocate TX fifo\n");
		goto err_put_dev;
	}

	tx_pipe->fifo = qcom_smem_get(remote_pid, SMEM_GLINK_NATIVE_XPRT_FIFO_0,
				      &tx_pipe->native.length);
	if (IS_ERR(tx_pipe->fifo)) {
		dev_err(dev, "failed to acquire TX fifo\n");
		ret = PTR_ERR(tx_pipe->fifo);
		goto err_put_dev;
	}

	rx_pipe->native.avail = glink_smem_rx_avail;
	rx_pipe->native.peak = glink_smem_rx_peak;
	rx_pipe->native.advance = glink_smem_rx_advance;
	rx_pipe->remote_pid = remote_pid;

	tx_pipe->native.avail = glink_smem_tx_avail;
	tx_pipe->native.write = glink_smem_tx_write;
	tx_pipe->remote_pid = remote_pid;

	*rx_pipe->tail = 0;
	*tx_pipe->head = 0;

	glink = qcom_glink_native_probe(dev,
					GLINK_FEATURE_INTENT_REUSE,
					&rx_pipe->native, &tx_pipe->native,
					false);
	if (IS_ERR(glink)) {
		ret = PTR_ERR(glink);
		goto err_put_dev;
	}

	return glink;

err_put_dev:
	device_unregister(dev);

	return ERR_PTR(ret);
}