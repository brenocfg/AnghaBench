#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvif_object {int dummy; } ;
struct TYPE_4__ {struct nvif_object object; } ;
struct TYPE_5__ {TYPE_1__ device; } ;
struct nouveau_drm {struct backlight_device* backlight; int /*<<< orphan*/  bl_connectors; TYPE_2__ client; } ;
struct drm_connector {int /*<<< orphan*/  kdev; int /*<<< orphan*/  dev; } ;
struct backlight_properties {int max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int /*<<< orphan*/  brightness; } ;
struct backlight_device {TYPE_3__ props; } ;
struct backlight_connector {scalar_t__ id; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int BL_NAME_SIZE ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  NV40_PMC_BACKLIGHT ; 
 int NV40_PMC_BACKLIGHT_MASK ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 struct backlight_device* backlight_device_register (char*,int /*<<< orphan*/ ,struct nouveau_drm*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  bl_ida ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_get_backlight_name (char*,struct backlight_connector*) ; 
 int /*<<< orphan*/  nv40_bl_ops ; 
 int /*<<< orphan*/  nv40_get_intensity (struct backlight_device*) ; 
 int nvif_rd32 (struct nvif_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv40_backlight_init(struct drm_connector *connector)
{
	struct nouveau_drm *drm = nouveau_drm(connector->dev);
	struct nvif_object *device = &drm->client.device.object;
	struct backlight_properties props;
	struct backlight_device *bd;
	struct backlight_connector bl_connector;
	char backlight_name[BL_NAME_SIZE];

	if (!(nvif_rd32(device, NV40_PMC_BACKLIGHT) & NV40_PMC_BACKLIGHT_MASK))
		return 0;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = 31;
	if (!nouveau_get_backlight_name(backlight_name, &bl_connector)) {
		NV_ERROR(drm, "Failed to retrieve a unique name for the backlight interface\n");
		return 0;
	}
	bd = backlight_device_register(backlight_name , connector->kdev, drm,
				       &nv40_bl_ops, &props);

	if (IS_ERR(bd)) {
		if (bl_connector.id >= 0)
			ida_simple_remove(&bl_ida, bl_connector.id);
		return PTR_ERR(bd);
	}
	list_add(&bl_connector.head, &drm->bl_connectors);
	drm->backlight = bd;
	bd->props.brightness = nv40_get_intensity(bd);
	backlight_update_status(bd);

	return 0;
}