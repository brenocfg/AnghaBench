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
struct drm_encoder {int /*<<< orphan*/  head; int /*<<< orphan*/  name; int /*<<< orphan*/  base; struct drm_bridge* bridge; struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_encoder; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct drm_bridge {struct drm_bridge* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_bridge_detach (struct drm_bridge*) ; 
 int /*<<< orphan*/  drm_mode_object_unregister (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct drm_encoder*,int /*<<< orphan*/ ,int) ; 

void drm_encoder_cleanup(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;

	/* Note that the encoder_list is considered to be static; should we
	 * remove the drm_encoder at runtime we would have to decrement all
	 * the indices on the drm_encoder after us in the encoder_list.
	 */

	if (encoder->bridge) {
		struct drm_bridge *bridge = encoder->bridge;
		struct drm_bridge *next;

		while (bridge) {
			next = bridge->next;
			drm_bridge_detach(bridge);
			bridge = next;
		}
	}

	drm_mode_object_unregister(dev, &encoder->base);
	kfree(encoder->name);
	list_del(&encoder->head);
	dev->mode_config.num_encoder--;

	memset(encoder, 0, sizeof(*encoder));
}