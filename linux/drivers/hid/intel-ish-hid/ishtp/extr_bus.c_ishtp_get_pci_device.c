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
struct ishtp_cl_device {TYPE_1__* ishtp_dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* devc; } ;

/* Variables and functions */

struct device *ishtp_get_pci_device(struct ishtp_cl_device *device)
{
	return device->ishtp_dev->devc;
}