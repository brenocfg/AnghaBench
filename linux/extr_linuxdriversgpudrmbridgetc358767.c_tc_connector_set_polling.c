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
struct tc_data {int dummy; } ;
struct drm_connector {int polled; } ;

/* Variables and functions */
 int DRM_CONNECTOR_POLL_CONNECT ; 
 int DRM_CONNECTOR_POLL_DISCONNECT ; 

__attribute__((used)) static void tc_connector_set_polling(struct tc_data *tc,
				     struct drm_connector *connector)
{
	/* TODO: add support for HPD */
	connector->polled = DRM_CONNECTOR_POLL_CONNECT |
			    DRM_CONNECTOR_POLL_DISCONNECT;
}