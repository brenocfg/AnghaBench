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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_coredumpm (struct device*,int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devcd_freev ; 
 int /*<<< orphan*/  devcd_readv ; 

void dev_coredumpv(struct device *dev, void *data, size_t datalen,
		   gfp_t gfp)
{
	dev_coredumpm(dev, NULL, data, datalen, gfp, devcd_readv, devcd_freev);
}