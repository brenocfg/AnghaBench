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
struct gnss_device {size_t type; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t GNSS_TYPE_COUNT ; 
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ *,char*) ; 
 char** gnss_type_names ; 

__attribute__((used)) static const char *gnss_type_name(struct gnss_device *gdev)
{
	const char *name = NULL;

	if (gdev->type < GNSS_TYPE_COUNT)
		name = gnss_type_names[gdev->type];

	if (!name)
		dev_WARN(&gdev->dev, "type name not defined\n");

	return name;
}