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

/* Variables and functions */
 int rndis_set_config_parameter (struct usbnet*,char*,int,char*) ; 

__attribute__((used)) static int rndis_set_config_parameter_str(struct usbnet *dev,
						char *param, char *value)
{
	return rndis_set_config_parameter(dev, param, 2, value);
}