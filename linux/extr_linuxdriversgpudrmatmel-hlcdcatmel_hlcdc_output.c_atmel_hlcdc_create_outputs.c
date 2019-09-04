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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int atmel_hlcdc_attach_endpoint (struct drm_device*,int) ; 

int atmel_hlcdc_create_outputs(struct drm_device *dev)
{
	int endpoint, ret = 0;

	for (endpoint = 0; !ret; endpoint++)
		ret = atmel_hlcdc_attach_endpoint(dev, endpoint);

	/* At least one device was successfully attached.*/
	if (ret == -ENODEV && endpoint)
		return 0;

	return ret;
}