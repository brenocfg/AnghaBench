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
struct usbnet {int dummy; } ;
struct mcs7830_data {int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIF_REG_CONFIG ; 
 struct mcs7830_data* mcs7830_get_data (struct usbnet*) ; 
 int /*<<< orphan*/  mcs7830_set_reg_async (struct usbnet*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mcs7830_hif_update_config(struct usbnet *dev)
{
	/* implementation specific to data->config
           (argument needs to be heap-based anyway - USB DMA!) */
	struct mcs7830_data *data = mcs7830_get_data(dev);
	mcs7830_set_reg_async(dev, HIF_REG_CONFIG, 1, &data->config);
}