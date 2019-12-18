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
struct TYPE_2__ {scalar_t__ non_desktop; } ;
struct drm_connector {scalar_t__ status; TYPE_1__ display_info; } ;

/* Variables and functions */
 scalar_t__ connector_status_connected ; 
 scalar_t__ connector_status_disconnected ; 

__attribute__((used)) static bool drm_connector_enabled(struct drm_connector *connector, bool strict)
{
	bool enable;

	if (connector->display_info.non_desktop)
		return false;

	if (strict)
		enable = connector->status == connector_status_connected;
	else
		enable = connector->status != connector_status_disconnected;

	return enable;
}