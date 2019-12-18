#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct reserved_mem {int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;
struct qcom_scm_vmperm {void* perm; void* vmid; } ;
struct TYPE_12__ {int /*<<< orphan*/  devt; int /*<<< orphan*/ * class; void* id; int /*<<< orphan*/  release; int /*<<< orphan*/  groups; TYPE_5__* parent; } ;
struct TYPE_14__ {int /*<<< orphan*/  owner; } ;
struct qcom_rmtfs_mem {TYPE_1__ dev; TYPE_7__ cdev; int /*<<< orphan*/  perms; int /*<<< orphan*/  size; int /*<<< orphan*/  addr; int /*<<< orphan*/  base; void* client_id; } ;
struct TYPE_13__ {struct device_node* of_node; } ;
struct platform_device {TYPE_5__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (void*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMREMAP_WC ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,void*) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 void* QCOM_SCM_PERM_RW ; 
 void* QCOM_SCM_VMID_HLOS ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int cdev_device_add (TYPE_7__*,TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_device_del (TYPE_7__*,TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_5__*,struct qcom_rmtfs_mem*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,void*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  devm_memremap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qcom_rmtfs_mem* kzalloc (int,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,void**) ; 
 struct reserved_mem* of_reserved_mem_lookup (struct device_node*) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  qcom_rmtfs_mem_fops ; 
 int /*<<< orphan*/  qcom_rmtfs_mem_groups ; 
 int /*<<< orphan*/  qcom_rmtfs_mem_major ; 
 int /*<<< orphan*/  qcom_rmtfs_mem_release_device ; 
 int qcom_scm_assign_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct qcom_scm_vmperm*,int) ; 
 int /*<<< orphan*/  qcom_scm_is_available () ; 
 int /*<<< orphan*/  rmtfs_class ; 

__attribute__((used)) static int qcom_rmtfs_mem_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct qcom_scm_vmperm perms[2];
	struct reserved_mem *rmem;
	struct qcom_rmtfs_mem *rmtfs_mem;
	u32 client_id;
	u32 vmid;
	int ret;

	rmem = of_reserved_mem_lookup(node);
	if (!rmem) {
		dev_err(&pdev->dev, "failed to acquire memory region\n");
		return -EINVAL;
	}

	ret = of_property_read_u32(node, "qcom,client-id", &client_id);
	if (ret) {
		dev_err(&pdev->dev, "failed to parse \"qcom,client-id\"\n");
		return ret;

	}

	rmtfs_mem = kzalloc(sizeof(*rmtfs_mem), GFP_KERNEL);
	if (!rmtfs_mem)
		return -ENOMEM;

	rmtfs_mem->addr = rmem->base;
	rmtfs_mem->client_id = client_id;
	rmtfs_mem->size = rmem->size;

	device_initialize(&rmtfs_mem->dev);
	rmtfs_mem->dev.parent = &pdev->dev;
	rmtfs_mem->dev.groups = qcom_rmtfs_mem_groups;
	rmtfs_mem->dev.release = qcom_rmtfs_mem_release_device;

	rmtfs_mem->base = devm_memremap(&rmtfs_mem->dev, rmtfs_mem->addr,
					rmtfs_mem->size, MEMREMAP_WC);
	if (IS_ERR(rmtfs_mem->base)) {
		dev_err(&pdev->dev, "failed to remap rmtfs_mem region\n");
		ret = PTR_ERR(rmtfs_mem->base);
		goto put_device;
	}

	cdev_init(&rmtfs_mem->cdev, &qcom_rmtfs_mem_fops);
	rmtfs_mem->cdev.owner = THIS_MODULE;

	dev_set_name(&rmtfs_mem->dev, "qcom_rmtfs_mem%d", client_id);
	rmtfs_mem->dev.id = client_id;
	rmtfs_mem->dev.class = &rmtfs_class;
	rmtfs_mem->dev.devt = MKDEV(MAJOR(qcom_rmtfs_mem_major), client_id);

	ret = cdev_device_add(&rmtfs_mem->cdev, &rmtfs_mem->dev);
	if (ret) {
		dev_err(&pdev->dev, "failed to add cdev: %d\n", ret);
		goto put_device;
	}

	ret = of_property_read_u32(node, "qcom,vmid", &vmid);
	if (ret < 0 && ret != -EINVAL) {
		dev_err(&pdev->dev, "failed to parse qcom,vmid\n");
		goto remove_cdev;
	} else if (!ret) {
		if (!qcom_scm_is_available()) {
			ret = -EPROBE_DEFER;
			goto remove_cdev;
		}

		perms[0].vmid = QCOM_SCM_VMID_HLOS;
		perms[0].perm = QCOM_SCM_PERM_RW;
		perms[1].vmid = vmid;
		perms[1].perm = QCOM_SCM_PERM_RW;

		rmtfs_mem->perms = BIT(QCOM_SCM_VMID_HLOS);
		ret = qcom_scm_assign_mem(rmtfs_mem->addr, rmtfs_mem->size,
					  &rmtfs_mem->perms, perms, 2);
		if (ret < 0) {
			dev_err(&pdev->dev, "assign memory failed\n");
			goto remove_cdev;
		}
	}

	dev_set_drvdata(&pdev->dev, rmtfs_mem);

	return 0;

remove_cdev:
	cdev_device_del(&rmtfs_mem->cdev, &rmtfs_mem->dev);
put_device:
	put_device(&rmtfs_mem->dev);

	return ret;
}