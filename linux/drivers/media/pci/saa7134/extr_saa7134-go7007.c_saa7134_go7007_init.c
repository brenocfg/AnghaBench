#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct saa7134_go7007 {int /*<<< orphan*/ * bottom; int /*<<< orphan*/ * top; int /*<<< orphan*/  status; int /*<<< orphan*/  vdev; int /*<<< orphan*/  v4l2_dev; TYPE_1__* board_info; struct v4l2_subdev sd; struct saa7134_dev* dev; struct saa7134_go7007* hpi_context; int /*<<< orphan*/ * hpi_ops; int /*<<< orphan*/  name; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  board_id; } ;
struct saa7134_dev {size_t board; int /*<<< orphan*/ * empress_dev; TYPE_3__* pci; } ;
struct go7007 {int /*<<< orphan*/ * bottom; int /*<<< orphan*/ * top; int /*<<< orphan*/  status; int /*<<< orphan*/  vdev; int /*<<< orphan*/  v4l2_dev; TYPE_1__* board_info; struct v4l2_subdev sd; struct saa7134_dev* dev; struct go7007* hpi_context; int /*<<< orphan*/ * hpi_ops; int /*<<< orphan*/  name; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  board_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {char* name; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  num_i2c_devs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GO7007_BOARDID_PCI_VOYAGER ; 
 int GO7007_BOARD_USE_ONBOARD_I2C ; 
 int /*<<< orphan*/  STATUS_ONLINE ; 
 int /*<<< orphan*/  board_voyager ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 struct saa7134_go7007* go7007_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ go7007_boot_encoder (struct saa7134_go7007*,int) ; 
 scalar_t__ go7007_register_encoder (struct saa7134_go7007*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct saa7134_go7007*) ; 
 struct saa7134_go7007* kzalloc (int,int /*<<< orphan*/ ) ; 
 char* pci_name (TYPE_3__*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 TYPE_2__* saa7134_boards ; 
 int /*<<< orphan*/  saa7134_go7007_hpi_ops ; 
 int /*<<< orphan*/  saa7134_go7007_sd_ops ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ v4l2_device_register_subdev (int /*<<< orphan*/ *,struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (struct v4l2_subdev*,struct saa7134_go7007*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int saa7134_go7007_init(struct saa7134_dev *dev)
{
	struct go7007 *go;
	struct saa7134_go7007 *saa;
	struct v4l2_subdev *sd;

	pr_debug("saa7134-go7007: probing new SAA713X board\n");

	go = go7007_alloc(&board_voyager, &dev->pci->dev);
	if (go == NULL)
		return -ENOMEM;

	saa = kzalloc(sizeof(struct saa7134_go7007), GFP_KERNEL);
	if (saa == NULL) {
		kfree(go);
		return -ENOMEM;
	}

	go->board_id = GO7007_BOARDID_PCI_VOYAGER;
	snprintf(go->bus_info, sizeof(go->bus_info), "PCI:%s", pci_name(dev->pci));
	strscpy(go->name, saa7134_boards[dev->board].name, sizeof(go->name));
	go->hpi_ops = &saa7134_go7007_hpi_ops;
	go->hpi_context = saa;
	saa->dev = dev;

	/* Init the subdevice interface */
	sd = &saa->sd;
	v4l2_subdev_init(sd, &saa7134_go7007_sd_ops);
	v4l2_set_subdevdata(sd, saa);
	strscpy(sd->name, "saa7134-go7007", sizeof(sd->name));

	/* Allocate a couple pages for receiving the compressed stream */
	saa->top = (u8 *)get_zeroed_page(GFP_KERNEL);
	if (!saa->top)
		goto allocfail;
	saa->bottom = (u8 *)get_zeroed_page(GFP_KERNEL);
	if (!saa->bottom)
		goto allocfail;

	/* Boot the GO7007 */
	if (go7007_boot_encoder(go, go->board_info->flags &
					GO7007_BOARD_USE_ONBOARD_I2C) < 0)
		goto allocfail;

	/* Do any final GO7007 initialization, then register the
	 * V4L2 and ALSA interfaces */
	if (go7007_register_encoder(go, go->board_info->num_i2c_devs) < 0)
		goto allocfail;

	/* Register the subdevice interface with the go7007 device */
	if (v4l2_device_register_subdev(&go->v4l2_dev, sd) < 0)
		pr_info("saa7134-go7007: register subdev failed\n");

	dev->empress_dev = &go->vdev;

	go->status = STATUS_ONLINE;
	return 0;

allocfail:
	if (saa->top)
		free_page((unsigned long)saa->top);
	if (saa->bottom)
		free_page((unsigned long)saa->bottom);
	kfree(saa);
	kfree(go);
	return -ENOMEM;
}