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
struct TYPE_2__ {scalar_t__ helper_subtype; } ;
struct coresight_device {scalar_t__ type; TYPE_1__ subtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CORESIGHT_CATU ; 
 scalar_t__ CORESIGHT_DEV_SUBTYPE_HELPER_CATU ; 
 scalar_t__ CORESIGHT_DEV_TYPE_HELPER ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool coresight_is_catu_device(struct coresight_device *csdev)
{
	if (!IS_ENABLED(CONFIG_CORESIGHT_CATU))
		return false;
	if (csdev->type != CORESIGHT_DEV_TYPE_HELPER)
		return false;
	if (csdev->subtype.helper_subtype != CORESIGHT_DEV_SUBTYPE_HELPER_CATU)
		return false;
	return true;
}