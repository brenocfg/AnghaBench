#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ntb_msi_devres {void* entry; struct ntb_dev* ntb; } ;
struct ntb_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct ntb_dev* dev_ntb (struct device*) ; 

__attribute__((used)) static int ntbm_msi_callback_match(struct device *dev, void *res, void *data)
{
	struct ntb_dev *ntb = dev_ntb(dev);
	struct ntb_msi_devres *dr = res;

	return dr->ntb == ntb && dr->entry == data;
}