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
struct sdio_func {struct sdio_func* tmpbuf; struct sdio_func* info; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct sdio_func* dev_to_sdio_func (struct device*) ; 
 int /*<<< orphan*/  kfree (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_free_func_cis (struct sdio_func*) ; 

__attribute__((used)) static void sdio_release_func(struct device *dev)
{
	struct sdio_func *func = dev_to_sdio_func(dev);

	sdio_free_func_cis(func);

	kfree(func->info);
	kfree(func->tmpbuf);
	kfree(func);
}