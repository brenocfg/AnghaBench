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
struct tinydrm_connector {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct tinydrm_connector*) ; 
 struct tinydrm_connector* to_tinydrm_connector (struct drm_connector*) ; 

__attribute__((used)) static void tinydrm_connector_destroy(struct drm_connector *connector)
{
	struct tinydrm_connector *tconn = to_tinydrm_connector(connector);

	drm_connector_cleanup(connector);
	kfree(tconn);
}