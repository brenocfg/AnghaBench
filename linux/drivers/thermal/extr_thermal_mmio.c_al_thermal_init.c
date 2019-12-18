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
struct thermal_mmio {int mask; int factor; int /*<<< orphan*/  read_mmio; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  thermal_mmio_readb ; 

__attribute__((used)) static int al_thermal_init(struct platform_device *pdev,
			   struct thermal_mmio *sensor)
{
	sensor->read_mmio = thermal_mmio_readb;
	sensor->mask = 0xff;
	sensor->factor = 1000;

	return 0;
}