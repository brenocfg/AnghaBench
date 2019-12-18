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
struct wacom_features {int x_resolution; int x_phy; int x_max; int y_phy; int y_max; int y_resolution; } ;

/* Variables and functions */

__attribute__((used)) static void wacom_set_default_phy(struct wacom_features *features)
{
	if (features->x_resolution) {
		features->x_phy = (features->x_max * 100) /
					features->x_resolution;
		features->y_phy = (features->y_max * 100) /
					features->y_resolution;
	}
}