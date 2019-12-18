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
struct wl1251 {int /*<<< orphan*/  vio; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 struct wl1251* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  wl1251_free_hw (struct wl1251*) ; 

__attribute__((used)) static int wl1251_spi_remove(struct spi_device *spi)
{
	struct wl1251 *wl = spi_get_drvdata(spi);

	wl1251_free_hw(wl);
	regulator_disable(wl->vio);

	return 0;
}