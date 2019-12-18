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
struct typec_altmode {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  mux; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct typec_altmode*) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_altmode (struct typec_altmode*) ; 
 int /*<<< orphan*/  typec_mux_put (int /*<<< orphan*/ ) ; 

void typec_unregister_altmode(struct typec_altmode *adev)
{
	if (IS_ERR_OR_NULL(adev))
		return;
	typec_mux_put(to_altmode(adev)->mux);
	device_unregister(&adev->dev);
}