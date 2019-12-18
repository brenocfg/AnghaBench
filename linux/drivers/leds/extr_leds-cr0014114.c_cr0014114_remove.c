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
struct spi_device {int dummy; } ;
struct cr0014114 {int /*<<< orphan*/  lock; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct cr0014114* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int cr0014114_remove(struct spi_device *spi)
{
	struct cr0014114 *priv = spi_get_drvdata(spi);

	cancel_delayed_work_sync(&priv->work);
	mutex_destroy(&priv->lock);

	return 0;
}