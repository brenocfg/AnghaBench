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
struct mga_connector {int /*<<< orphan*/  i2c; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct drm_connector*) ; 
 int /*<<< orphan*/  mgag200_i2c_destroy (int /*<<< orphan*/ ) ; 
 struct mga_connector* to_mga_connector (struct drm_connector*) ; 

__attribute__((used)) static void mga_connector_destroy(struct drm_connector *connector)
{
	struct mga_connector *mga_connector = to_mga_connector(connector);
	mgag200_i2c_destroy(mga_connector->i2c);
	drm_connector_cleanup(connector);
	kfree(connector);
}