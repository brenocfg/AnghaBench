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
struct ishtp_cl_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct ishtp_cl_device* to_ishtp_cl_device (struct device*) ; 

struct ishtp_cl_device *ishtp_dev_to_cl_device(struct device *device)
{
	return to_ishtp_cl_device(device);
}