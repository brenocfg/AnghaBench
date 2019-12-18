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
struct flexcop_device {struct flexcop_device* bus_specific; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct flexcop_device*) ; 

void flexcop_device_kfree(struct flexcop_device *fc)
{
	kfree(fc->bus_specific);
	kfree(fc);
}