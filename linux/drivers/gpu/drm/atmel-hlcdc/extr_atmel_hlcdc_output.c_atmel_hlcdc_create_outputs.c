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
	int attached = 0;

	/*
	 * Always scan the first few endpoints even if we get -ENODEV,
	 * but keep going after that as long as we keep getting hits.
	 */
	for (endpoint = 0; !ret || endpoint < 4; endpoint++) {
		ret = atmel_hlcdc_attach_endpoint(dev, endpoint);
		if (ret == -ENODEV)
			continue;
		if (ret)
			break;
		attached++;
	}

	/* At least one device was successfully attached.*/
	if (ret == -ENODEV && attached)
		return 0;

	return ret;
}