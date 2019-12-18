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
typedef  int /*<<< orphan*/  uint8_t ;
struct drm_connector {int /*<<< orphan*/  eld; } ;
struct zx_hdmi {struct drm_connector connector; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct zx_hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,size_t) ; 

__attribute__((used)) static int zx_hdmi_audio_get_eld(struct device *dev, void *data,
				 uint8_t *buf, size_t len)
{
	struct zx_hdmi *hdmi = dev_get_drvdata(dev);
	struct drm_connector *connector = &hdmi->connector;

	memcpy(buf, connector->eld, min(sizeof(connector->eld), len));

	return 0;
}