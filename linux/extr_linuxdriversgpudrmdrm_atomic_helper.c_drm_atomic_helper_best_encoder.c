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
struct drm_encoder {int dummy; } ;
struct drm_connector {int /*<<< orphan*/ * encoder_ids; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct drm_encoder* drm_encoder_find (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct drm_encoder *
drm_atomic_helper_best_encoder(struct drm_connector *connector)
{
	WARN_ON(connector->encoder_ids[1]);
	return drm_encoder_find(connector->dev, NULL, connector->encoder_ids[0]);
}