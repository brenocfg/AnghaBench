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
struct smssdio_device {int /*<<< orphan*/  coredev; scalar_t__ split_cb; } ;
struct sdio_func {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct smssdio_device*) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_disable_func (struct sdio_func*) ; 
 struct smssdio_device* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_irq (struct sdio_func*) ; 
 int /*<<< orphan*/  smscore_putbuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  smscore_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smssdio_remove(struct sdio_func *func)
{
	struct smssdio_device *smsdev;

	smsdev = sdio_get_drvdata(func);

	/* FIXME: racy! */
	if (smsdev->split_cb)
		smscore_putbuffer(smsdev->coredev, smsdev->split_cb);

	smscore_unregister_device(smsdev->coredev);

	sdio_claim_host(func);
	sdio_release_irq(func);
	sdio_disable_func(func);
	sdio_release_host(func);

	kfree(smsdev);
}