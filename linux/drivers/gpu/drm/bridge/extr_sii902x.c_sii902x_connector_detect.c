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
struct sii902x {int /*<<< orphan*/  mutex; int /*<<< orphan*/  regmap; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int /*<<< orphan*/  SII902X_INT_STATUS ; 
 unsigned int SII902X_PLUGGED_STATUS ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 struct sii902x* connector_to_sii902x (struct drm_connector*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static enum drm_connector_status
sii902x_connector_detect(struct drm_connector *connector, bool force)
{
	struct sii902x *sii902x = connector_to_sii902x(connector);
	unsigned int status;

	mutex_lock(&sii902x->mutex);

	regmap_read(sii902x->regmap, SII902X_INT_STATUS, &status);

	mutex_unlock(&sii902x->mutex);

	return (status & SII902X_PLUGGED_STATUS) ?
	       connector_status_connected : connector_status_disconnected;
}