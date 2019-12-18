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
struct trf7970a {int /*<<< orphan*/  lock; int /*<<< orphan*/  regulator; int /*<<< orphan*/  ddev; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_digital_free_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_digital_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 struct trf7970a* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  trf7970a_shutdown (struct trf7970a*) ; 

__attribute__((used)) static int trf7970a_remove(struct spi_device *spi)
{
	struct trf7970a *trf = spi_get_drvdata(spi);

	mutex_lock(&trf->lock);

	trf7970a_shutdown(trf);

	mutex_unlock(&trf->lock);

	nfc_digital_unregister_device(trf->ddev);
	nfc_digital_free_device(trf->ddev);

	regulator_disable(trf->regulator);

	mutex_destroy(&trf->lock);

	return 0;
}