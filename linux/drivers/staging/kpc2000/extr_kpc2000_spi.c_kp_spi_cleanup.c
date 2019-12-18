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
struct spi_device {struct kp_spi_controller_state* controller_state; } ;
struct kp_spi_controller_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct kp_spi_controller_state*) ; 

__attribute__((used)) static void
kp_spi_cleanup(struct spi_device *spidev)
{
	struct kp_spi_controller_state *cs = spidev->controller_state;

	kfree(cs);
}