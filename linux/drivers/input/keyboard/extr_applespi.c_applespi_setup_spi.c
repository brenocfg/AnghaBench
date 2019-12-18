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
struct applespi_data {int /*<<< orphan*/  drain_complete; int /*<<< orphan*/  cmd_msg_lock; } ;

/* Variables and functions */
 int applespi_get_spi_settings (struct applespi_data*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int applespi_setup_spi(struct applespi_data *applespi)
{
	int sts;

	sts = applespi_get_spi_settings(applespi);
	if (sts)
		return sts;

	spin_lock_init(&applespi->cmd_msg_lock);
	init_waitqueue_head(&applespi->drain_complete);

	return 0;
}