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
struct hsi_client {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;
struct hsc_client_data {TYPE_1__ cdev; struct hsc_channel* channels; struct hsi_client* cl; int /*<<< orphan*/  lock; } ;
struct hsc_channel {int ch; struct hsc_client_data* cl_data; struct hsi_client* cl; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int HSC_BASEMINOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HSC_DEVS ; 
 scalar_t__ MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int alloc_chrdev_region (int /*<<< orphan*/ *,unsigned int,int,char const*) ; 
 int cdev_add (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  hsc_channel_init (struct hsc_channel*) ; 
 int /*<<< orphan*/  hsc_fops ; 
 scalar_t__ hsc_major ; 
 int /*<<< orphan*/  hsi_client_set_drvdata (struct hsi_client*,struct hsc_client_data*) ; 
 int /*<<< orphan*/  hsi_id (struct hsi_client*) ; 
 int /*<<< orphan*/  hsi_port_id (struct hsi_client*) ; 
 int /*<<< orphan*/  kfree (struct hsc_client_data*) ; 
 struct hsc_client_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int register_chrdev_region (int /*<<< orphan*/ ,int,char const*) ; 
 struct hsi_client* to_hsi_client (struct device*) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hsc_probe(struct device *dev)
{
	const char devname[] = "hsi_char";
	struct hsc_client_data *cl_data;
	struct hsc_channel *channel;
	struct hsi_client *cl = to_hsi_client(dev);
	unsigned int hsc_baseminor;
	dev_t hsc_dev;
	int ret;
	int i;

	cl_data = kzalloc(sizeof(*cl_data), GFP_KERNEL);
	if (!cl_data)
		return -ENOMEM;

	hsc_baseminor = HSC_BASEMINOR(hsi_id(cl), hsi_port_id(cl));
	if (!hsc_major) {
		ret = alloc_chrdev_region(&hsc_dev, hsc_baseminor,
						HSC_DEVS, devname);
		if (ret == 0)
			hsc_major = MAJOR(hsc_dev);
	} else {
		hsc_dev = MKDEV(hsc_major, hsc_baseminor);
		ret = register_chrdev_region(hsc_dev, HSC_DEVS, devname);
	}
	if (ret < 0) {
		dev_err(dev, "Device %s allocation failed %d\n",
					hsc_major ? "minor" : "major", ret);
		goto out1;
	}
	mutex_init(&cl_data->lock);
	hsi_client_set_drvdata(cl, cl_data);
	cdev_init(&cl_data->cdev, &hsc_fops);
	cl_data->cdev.owner = THIS_MODULE;
	cl_data->cl = cl;
	for (i = 0, channel = cl_data->channels; i < HSC_DEVS; i++, channel++) {
		hsc_channel_init(channel);
		channel->ch = i;
		channel->cl = cl;
		channel->cl_data = cl_data;
	}

	/* 1 hsi client -> N char devices (one for each channel) */
	ret = cdev_add(&cl_data->cdev, hsc_dev, HSC_DEVS);
	if (ret) {
		dev_err(dev, "Could not add char device %d\n", ret);
		goto out2;
	}

	return 0;
out2:
	unregister_chrdev_region(hsc_dev, HSC_DEVS);
out1:
	kfree(cl_data);

	return ret;
}