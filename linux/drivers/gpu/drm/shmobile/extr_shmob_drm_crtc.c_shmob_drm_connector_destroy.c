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
struct shmob_drm_connector {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_unregister (struct drm_connector*) ; 
 int /*<<< orphan*/  shmob_drm_backlight_exit (struct shmob_drm_connector*) ; 
 struct shmob_drm_connector* to_shmob_connector (struct drm_connector*) ; 

__attribute__((used)) static void shmob_drm_connector_destroy(struct drm_connector *connector)
{
	struct shmob_drm_connector *scon = to_shmob_connector(connector);

	shmob_drm_backlight_exit(scon);
	drm_connector_unregister(connector);
	drm_connector_cleanup(connector);
}