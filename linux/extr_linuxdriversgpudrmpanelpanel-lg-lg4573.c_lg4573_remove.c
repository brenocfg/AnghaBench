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
struct lg4573 {int /*<<< orphan*/  panel; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_panel_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lg4573_display_off (struct lg4573*) ; 
 struct lg4573* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int lg4573_remove(struct spi_device *spi)
{
	struct lg4573 *ctx = spi_get_drvdata(spi);

	lg4573_display_off(ctx);
	drm_panel_remove(&ctx->panel);

	return 0;
}