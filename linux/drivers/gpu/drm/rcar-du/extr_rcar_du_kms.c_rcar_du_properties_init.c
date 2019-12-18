#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * colorkey; } ;
struct rcar_du_device {TYPE_1__ props; int /*<<< orphan*/  ddev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * drm_property_create_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rcar_du_properties_init(struct rcar_du_device *rcdu)
{
	/*
	 * The color key is expressed as an RGB888 triplet stored in a 32-bit
	 * integer in XRGB8888 format. Bit 24 is used as a flag to disable (0)
	 * or enable source color keying (1).
	 */
	rcdu->props.colorkey =
		drm_property_create_range(rcdu->ddev, 0, "colorkey",
					  0, 0x01ffffff);
	if (rcdu->props.colorkey == NULL)
		return -ENOMEM;

	return 0;
}