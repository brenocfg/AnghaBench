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
struct device {int /*<<< orphan*/  of_node; } ;
struct rpmsg_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fops; int /*<<< orphan*/  name; int /*<<< orphan*/  minor; } ;
struct fastrpc_channel_ctx {int domain_id; struct rpmsg_device* rpdev; int /*<<< orphan*/  ctx_idr; int /*<<< orphan*/  lock; int /*<<< orphan*/  users; int /*<<< orphan*/  refcount; TYPE_1__ miscdev; } ;

/* Variables and functions */
 int CDSP_DOMAIN_ID ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MISC_DYNAMIC_MINOR ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct fastrpc_channel_ctx*) ; 
 int /*<<< orphan*/  dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * domains ; 
 int /*<<< orphan*/  fastrpc_fops ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct fastrpc_channel_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int misc_register (TYPE_1__*) ; 
 int of_platform_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 int of_property_read_string (int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int fastrpc_rpmsg_probe(struct rpmsg_device *rpdev)
{
	struct device *rdev = &rpdev->dev;
	struct fastrpc_channel_ctx *data;
	int i, err, domain_id = -1;
	const char *domain;

	err = of_property_read_string(rdev->of_node, "label", &domain);
	if (err) {
		dev_info(rdev, "FastRPC Domain not specified in DT\n");
		return err;
	}

	for (i = 0; i <= CDSP_DOMAIN_ID; i++) {
		if (!strcmp(domains[i], domain)) {
			domain_id = i;
			break;
		}
	}

	if (domain_id < 0) {
		dev_info(rdev, "FastRPC Invalid Domain ID %d\n", domain_id);
		return -EINVAL;
	}

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->miscdev.minor = MISC_DYNAMIC_MINOR;
	data->miscdev.name = kasprintf(GFP_KERNEL, "fastrpc-%s",
				domains[domain_id]);
	data->miscdev.fops = &fastrpc_fops;
	err = misc_register(&data->miscdev);
	if (err)
		return err;

	kref_init(&data->refcount);

	dev_set_drvdata(&rpdev->dev, data);
	dma_set_mask_and_coherent(rdev, DMA_BIT_MASK(32));
	INIT_LIST_HEAD(&data->users);
	spin_lock_init(&data->lock);
	idr_init(&data->ctx_idr);
	data->domain_id = domain_id;
	data->rpdev = rpdev;

	return of_platform_populate(rdev->of_node, NULL, NULL, rdev);
}