#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_connector {TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; } ;
struct TYPE_4__ {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int drm_add_modes_noedid (struct drm_connector*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_set_preferred_mode (struct drm_connector*,int,int) ; 

__attribute__((used)) static int cirrus_conn_get_modes(struct drm_connector *conn)
{
	int count;

	count = drm_add_modes_noedid(conn,
				     conn->dev->mode_config.max_width,
				     conn->dev->mode_config.max_height);
	drm_set_preferred_mode(conn, 1024, 768);
	return count;
}