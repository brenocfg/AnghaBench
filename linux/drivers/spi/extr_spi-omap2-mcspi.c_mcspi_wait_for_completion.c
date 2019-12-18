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
struct omap2_mcspi {scalar_t__ slave_aborted; int /*<<< orphan*/  master; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ spi_controller_is_slave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (struct completion*) ; 
 scalar_t__ wait_for_completion_interruptible (struct completion*) ; 

__attribute__((used)) static int mcspi_wait_for_completion(struct  omap2_mcspi *mcspi,
				     struct completion *x)
{
	if (spi_controller_is_slave(mcspi->master)) {
		if (wait_for_completion_interruptible(x) ||
		    mcspi->slave_aborted)
			return -EINTR;
	} else {
		wait_for_completion(x);
	}

	return 0;
}