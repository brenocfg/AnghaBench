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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct qxl_urect {scalar_t__ left; scalar_t__ top; scalar_t__ right; scalar_t__ bottom; } ;
struct qxl_head {scalar_t__ x; scalar_t__ y; scalar_t__ width; scalar_t__ height; scalar_t__ surface_id; int id; scalar_t__ flags; } ;
struct qxl_device {TYPE_3__* client_monitors_config; TYPE_2__* rom; } ;
struct TYPE_6__ {int count; int max_allowed; struct qxl_head* heads; } ;
struct TYPE_4__ {int count; struct qxl_urect* heads; } ;
struct TYPE_5__ {scalar_t__ client_monitors_config_crc; TYPE_1__ client_monitors_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int MONITORS_CONFIG_BAD_CRC ; 
 int MONITORS_CONFIG_ERROR ; 
 int MONITORS_CONFIG_MODIFIED ; 
 int MONITORS_CONFIG_UNCHANGED ; 
 scalar_t__ crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ qxl_alloc_client_monitors_config (struct qxl_device*,int) ; 
 int qxl_num_crtc ; 

__attribute__((used)) static int qxl_display_copy_rom_client_monitors_config(struct qxl_device *qdev)
{
	int i;
	int num_monitors;
	uint32_t crc;
	int status = MONITORS_CONFIG_UNCHANGED;

	num_monitors = qdev->rom->client_monitors_config.count;
	crc = crc32(0, (const uint8_t *)&qdev->rom->client_monitors_config,
		  sizeof(qdev->rom->client_monitors_config));
	if (crc != qdev->rom->client_monitors_config_crc)
		return MONITORS_CONFIG_BAD_CRC;
	if (!num_monitors) {
		DRM_DEBUG_KMS("no client monitors configured\n");
		return status;
	}
	if (num_monitors > qxl_num_crtc) {
		DRM_DEBUG_KMS("client monitors list will be truncated: %d < %d\n",
			      qxl_num_crtc, num_monitors);
		num_monitors = qxl_num_crtc;
	} else {
		num_monitors = qdev->rom->client_monitors_config.count;
	}
	if (qdev->client_monitors_config
	      && (num_monitors != qdev->client_monitors_config->count)) {
		status = MONITORS_CONFIG_MODIFIED;
	}
	if (qxl_alloc_client_monitors_config(qdev, num_monitors)) {
		status = MONITORS_CONFIG_ERROR;
		return status;
	}
	/* we copy max from the client but it isn't used */
	qdev->client_monitors_config->max_allowed = qxl_num_crtc;
	for (i = 0 ; i < qdev->client_monitors_config->count ; ++i) {
		struct qxl_urect *c_rect =
			&qdev->rom->client_monitors_config.heads[i];
		struct qxl_head *client_head =
			&qdev->client_monitors_config->heads[i];
		if (client_head->x != c_rect->left) {
			client_head->x = c_rect->left;
			status = MONITORS_CONFIG_MODIFIED;
		}
		if (client_head->y != c_rect->top) {
			client_head->y = c_rect->top;
			status = MONITORS_CONFIG_MODIFIED;
		}
		if (client_head->width != c_rect->right - c_rect->left) {
			client_head->width = c_rect->right - c_rect->left;
			status = MONITORS_CONFIG_MODIFIED;
		}
		if (client_head->height != c_rect->bottom - c_rect->top) {
			client_head->height = c_rect->bottom - c_rect->top;
			status = MONITORS_CONFIG_MODIFIED;
		}
		if (client_head->surface_id != 0) {
			client_head->surface_id = 0;
			status = MONITORS_CONFIG_MODIFIED;
		}
		if (client_head->id != i) {
			client_head->id = i;
			status = MONITORS_CONFIG_MODIFIED;
		}
		if (client_head->flags != 0) {
			client_head->flags = 0;
			status = MONITORS_CONFIG_MODIFIED;
		}
		DRM_DEBUG_KMS("read %dx%d+%d+%d\n", client_head->width, client_head->height,
			  client_head->x, client_head->y);
	}

	return status;
}