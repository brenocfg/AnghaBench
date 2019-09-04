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
struct adf_hw_device_data {int dummy; } ;
typedef  enum dev_sku_info { ____Placeholder_dev_sku_info } dev_sku_info ;

/* Variables and functions */
 int DEV_SKU_VF ; 

__attribute__((used)) static enum dev_sku_info get_sku(struct adf_hw_device_data *self)
{
	return DEV_SKU_VF;
}