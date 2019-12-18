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
struct cirrus_device {int /*<<< orphan*/  conn; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VGA ; 
 int /*<<< orphan*/  cirrus_conn_funcs ; 
 int /*<<< orphan*/  cirrus_conn_helper_funcs ; 
 int /*<<< orphan*/  drm_connector_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_connector_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cirrus_conn_init(struct cirrus_device *cirrus)
{
	drm_connector_helper_add(&cirrus->conn, &cirrus_conn_helper_funcs);
	return drm_connector_init(&cirrus->dev, &cirrus->conn,
				  &cirrus_conn_funcs, DRM_MODE_CONNECTOR_VGA);

}