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
struct nfcmrvl_private {struct nfcmrvl_i2c_drv_data* drv_data; } ;
struct nfcmrvl_i2c_drv_data {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static int nfcmrvl_i2c_nci_open(struct nfcmrvl_private *priv)
{
	struct nfcmrvl_i2c_drv_data *drv_data = priv->drv_data;

	if (!drv_data)
		return -ENODEV;

	return 0;
}