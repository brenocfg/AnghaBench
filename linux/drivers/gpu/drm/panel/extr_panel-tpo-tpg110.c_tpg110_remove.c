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
struct tpg110 {int /*<<< orphan*/  panel; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_panel_remove (int /*<<< orphan*/ *) ; 
 struct tpg110* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int tpg110_remove(struct spi_device *spi)
{
	struct tpg110 *tpg = spi_get_drvdata(spi);

	drm_panel_remove(&tpg->panel);
	return 0;
}