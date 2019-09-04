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
struct hdmi_connector {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  hdp_disable (struct hdmi_connector*) ; 
 int /*<<< orphan*/  kfree (struct hdmi_connector*) ; 
 struct hdmi_connector* to_hdmi_connector (struct drm_connector*) ; 

__attribute__((used)) static void hdmi_connector_destroy(struct drm_connector *connector)
{
	struct hdmi_connector *hdmi_connector = to_hdmi_connector(connector);

	hdp_disable(hdmi_connector);

	drm_connector_cleanup(connector);

	kfree(hdmi_connector);
}