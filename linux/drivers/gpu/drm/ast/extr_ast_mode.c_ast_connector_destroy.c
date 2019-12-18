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
struct drm_connector {int dummy; } ;
struct ast_connector {int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int /*<<< orphan*/  ast_i2c_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_unregister (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct drm_connector*) ; 
 struct ast_connector* to_ast_connector (struct drm_connector*) ; 

__attribute__((used)) static void ast_connector_destroy(struct drm_connector *connector)
{
	struct ast_connector *ast_connector = to_ast_connector(connector);
	ast_i2c_destroy(ast_connector->i2c);
	drm_connector_unregister(connector);
	drm_connector_cleanup(connector);
	kfree(connector);
}