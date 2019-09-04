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
struct fmc_device {int dummy; } ;

/* Variables and functions */
 int fmc_device_register_n_gw (struct fmc_device**,int,int /*<<< orphan*/ *) ; 

int fmc_device_register_n(struct fmc_device **devs, int n)
{
	return fmc_device_register_n_gw(devs, n, NULL);
}