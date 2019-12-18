#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ status; } ;
struct applespi_data {int /*<<< orphan*/  gpe; TYPE_2__ rd_m; TYPE_1__* spi; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_finish_gpe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  applespi_got_data (struct applespi_data*) ; 
 int /*<<< orphan*/  applespi_msg_complete (struct applespi_data*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,scalar_t__) ; 

__attribute__((used)) static void applespi_async_read_complete(void *context)
{
	struct applespi_data *applespi = context;

	if (applespi->rd_m.status < 0) {
		dev_warn(&applespi->spi->dev, "Error reading from device: %d\n",
			 applespi->rd_m.status);
		/*
		 * We don't actually know if this was a pure read, or a response
		 * to a write. But this is a rare error condition that should
		 * never occur, so clearing both flags to avoid deadlock.
		 */
		applespi_msg_complete(applespi, true, true);
	} else {
		applespi_got_data(applespi);
	}

	acpi_finish_gpe(NULL, applespi->gpe);
}