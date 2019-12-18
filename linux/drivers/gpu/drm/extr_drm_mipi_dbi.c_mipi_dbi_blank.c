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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct mipi_dbi {int dummy; } ;
struct TYPE_2__ {int min_height; int min_width; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct mipi_dbi_dev {scalar_t__ tx_buf; struct mipi_dbi dbi; struct drm_device drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DCS_SET_COLUMN_ADDRESS ; 
 int /*<<< orphan*/  MIPI_DCS_SET_PAGE_ADDRESS ; 
 int /*<<< orphan*/  MIPI_DCS_WRITE_MEMORY_START ; 
 int /*<<< orphan*/  drm_dev_enter (struct drm_device*,int*) ; 
 int /*<<< orphan*/  drm_dev_exit (int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mipi_dbi_command (struct mipi_dbi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mipi_dbi_command_buf (struct mipi_dbi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void mipi_dbi_blank(struct mipi_dbi_dev *dbidev)
{
	struct drm_device *drm = &dbidev->drm;
	u16 height = drm->mode_config.min_height;
	u16 width = drm->mode_config.min_width;
	struct mipi_dbi *dbi = &dbidev->dbi;
	size_t len = width * height * 2;
	int idx;

	if (!drm_dev_enter(drm, &idx))
		return;

	memset(dbidev->tx_buf, 0, len);

	mipi_dbi_command(dbi, MIPI_DCS_SET_COLUMN_ADDRESS, 0, 0,
			 (width >> 8) & 0xFF, (width - 1) & 0xFF);
	mipi_dbi_command(dbi, MIPI_DCS_SET_PAGE_ADDRESS, 0, 0,
			 (height >> 8) & 0xFF, (height - 1) & 0xFF);
	mipi_dbi_command_buf(dbi, MIPI_DCS_WRITE_MEMORY_START,
			     (u8 *)dbidev->tx_buf, len);

	drm_dev_exit(idx);
}