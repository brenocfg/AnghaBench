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
struct gb_host_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_hd_shutdown (struct gb_host_device*) ; 
 scalar_t__ is_gb_host_device (struct device*) ; 
 struct gb_host_device* to_gb_host_device (struct device*) ; 

__attribute__((used)) static void greybus_shutdown(struct device *dev)
{
	if (is_gb_host_device(dev)) {
		struct gb_host_device *hd;

		hd = to_gb_host_device(dev);
		gb_hd_shutdown(hd);
	}
}