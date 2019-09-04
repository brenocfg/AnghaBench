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
 int /*<<< orphan*/  fmc_device_unregister_n (struct fmc_device**,int) ; 

void fmc_device_unregister(struct fmc_device *fmc)
{
	fmc_device_unregister_n(&fmc, 1);
}