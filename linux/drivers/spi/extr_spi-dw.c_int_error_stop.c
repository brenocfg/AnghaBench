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
struct dw_spi {TYPE_2__* master; } ;
struct TYPE_4__ {TYPE_1__* cur_msg; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (TYPE_2__*) ; 
 int /*<<< orphan*/  spi_reset_chip (struct dw_spi*) ; 

__attribute__((used)) static void int_error_stop(struct dw_spi *dws, const char *msg)
{
	spi_reset_chip(dws);

	dev_err(&dws->master->dev, "%s\n", msg);
	dws->master->cur_msg->status = -EIO;
	spi_finalize_current_transfer(dws->master);
}