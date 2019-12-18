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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct i2c_adapter {int /*<<< orphan*/  name; TYPE_1__ dev; int /*<<< orphan*/ * algo_data; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; } ;
struct pt3_board {int /*<<< orphan*/ ** regs; struct pt3_board* i2c_buf; struct i2c_adapter i2c_adap; int /*<<< orphan*/  num_bufs; int /*<<< orphan*/  lock; struct pci_dev* pdev; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_DATA_BUFS ; 
 int /*<<< orphan*/  MIN_DATA_BUFS ; 
 int /*<<< orphan*/  PCI_REVISION_ID ; 
 int PT3_NUM_FE ; 
 int REG_VERSION ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clamp_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dma_set_coherent_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dma_set_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int i2c_add_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_del_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct pt3_board*) ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pt3_board*) ; 
 struct pt3_board* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct pt3_board* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  num_bufs ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 void* pci_ioremap_bar (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ *) ; 
 scalar_t__ pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct pt3_board*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pt3_alloc_adapter (struct pt3_board*,int) ; 
 int pt3_attach_fe (struct pt3_board*,int) ; 
 int /*<<< orphan*/  pt3_cleanup_adapter (struct pt3_board*,int /*<<< orphan*/ ) ; 
 int pt3_fe_init (struct pt3_board*) ; 
 int /*<<< orphan*/  pt3_i2c_algo ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pt3_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	u8 rev;
	u32 ver;
	int i, ret;
	struct pt3_board *pt3;
	struct i2c_adapter *i2c;

	if (pci_read_config_byte(pdev, PCI_REVISION_ID, &rev) || rev != 1)
		return -ENODEV;

	ret = pci_enable_device(pdev);
	if (ret < 0)
		return -ENODEV;
	pci_set_master(pdev);

	ret = pci_request_regions(pdev, DRV_NAME);
	if (ret < 0)
		goto err_disable_device;

	ret = dma_set_mask(&pdev->dev, DMA_BIT_MASK(64));
	if (ret == 0)
		dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(64));
	else {
		ret = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		if (ret == 0)
			dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
		else {
			dev_err(&pdev->dev, "Failed to set DMA mask\n");
			goto err_release_regions;
		}
		dev_info(&pdev->dev, "Use 32bit DMA\n");
	}

	pt3 = kzalloc(sizeof(*pt3), GFP_KERNEL);
	if (!pt3) {
		ret = -ENOMEM;
		goto err_release_regions;
	}
	pci_set_drvdata(pdev, pt3);
	pt3->pdev = pdev;
	mutex_init(&pt3->lock);
	pt3->regs[0] = pci_ioremap_bar(pdev, 0);
	pt3->regs[1] = pci_ioremap_bar(pdev, 2);
	if (pt3->regs[0] == NULL || pt3->regs[1] == NULL) {
		dev_err(&pdev->dev, "Failed to ioremap\n");
		ret = -ENOMEM;
		goto err_kfree;
	}

	ver = ioread32(pt3->regs[0] + REG_VERSION);
	if ((ver >> 16) != 0x0301) {
		dev_warn(&pdev->dev, "PT%d, I/F-ver.:%d not supported\n",
			 ver >> 24, (ver & 0x00ff0000) >> 16);
		ret = -ENODEV;
		goto err_iounmap;
	}

	pt3->num_bufs = clamp_val(num_bufs, MIN_DATA_BUFS, MAX_DATA_BUFS);

	pt3->i2c_buf = kmalloc(sizeof(*pt3->i2c_buf), GFP_KERNEL);
	if (pt3->i2c_buf == NULL) {
		ret = -ENOMEM;
		goto err_iounmap;
	}
	i2c = &pt3->i2c_adap;
	i2c->owner = THIS_MODULE;
	i2c->algo = &pt3_i2c_algo;
	i2c->algo_data = NULL;
	i2c->dev.parent = &pdev->dev;
	strscpy(i2c->name, DRV_NAME, sizeof(i2c->name));
	i2c_set_adapdata(i2c, pt3);
	ret = i2c_add_adapter(i2c);
	if (ret < 0)
		goto err_i2cbuf;

	for (i = 0; i < PT3_NUM_FE; i++) {
		ret = pt3_alloc_adapter(pt3, i);
		if (ret < 0)
			break;

		ret = pt3_attach_fe(pt3, i);
		if (ret < 0)
			break;
	}
	if (i < PT3_NUM_FE) {
		dev_err(&pdev->dev, "Failed to create FE%d\n", i);
		goto err_cleanup_adapters;
	}

	ret = pt3_fe_init(pt3);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to init frontends\n");
		i = PT3_NUM_FE - 1;
		goto err_cleanup_adapters;
	}

	dev_info(&pdev->dev,
		 "successfully init'ed PT%d (fw:0x%02x, I/F:0x%02x)\n",
		 ver >> 24, (ver >> 8) & 0xff, (ver >> 16) & 0xff);
	return 0;

err_cleanup_adapters:
	while (i >= 0)
		pt3_cleanup_adapter(pt3, i--);
	i2c_del_adapter(i2c);
err_i2cbuf:
	kfree(pt3->i2c_buf);
err_iounmap:
	if (pt3->regs[0])
		pci_iounmap(pdev, pt3->regs[0]);
	if (pt3->regs[1])
		pci_iounmap(pdev, pt3->regs[1]);
err_kfree:
	kfree(pt3);
err_release_regions:
	pci_release_regions(pdev);
err_disable_device:
	pci_disable_device(pdev);
	return ret;

}