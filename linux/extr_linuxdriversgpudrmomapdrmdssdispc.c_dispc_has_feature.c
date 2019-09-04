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
struct dispc_device {TYPE_1__* feat; } ;
typedef  enum dispc_feature_id { ____Placeholder_dispc_feature_id } dispc_feature_id ;
struct TYPE_2__ {unsigned int num_features; int* features; } ;

/* Variables and functions */

__attribute__((used)) static bool dispc_has_feature(struct dispc_device *dispc,
			      enum dispc_feature_id id)
{
	unsigned int i;

	for (i = 0; i < dispc->feat->num_features; i++) {
		if (dispc->feat->features[i] == id)
			return true;
	}

	return false;
}