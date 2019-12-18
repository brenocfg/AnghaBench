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
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct iss_resizer_device {TYPE_1__ subdev; } ;
struct iss_device {struct iss_resizer_device resizer; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 

void omap4iss_resizer_cleanup(struct iss_device *iss)
{
	struct iss_resizer_device *resizer = &iss->resizer;

	media_entity_cleanup(&resizer->subdev.entity);
}