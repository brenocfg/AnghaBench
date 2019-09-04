#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_4__ {struct drm_device* drm; } ;
struct mipi_dbi {scalar_t__ tx_buf; TYPE_2__ tinydrm; } ;
struct TYPE_3__ {int min_height; int min_width; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DCS_SET_COLUMN_ADDRESS ; 
 int /*<<< orphan*/  MIPI_DCS_SET_PAGE_ADDRESS ; 
 int /*<<< orphan*/  MIPI_DCS_WRITE_MEMORY_START ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mipi_dbi_command (struct mipi_dbi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mipi_dbi_command_buf (struct mipi_dbi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void mipi_dbi_blank(struct mipi_dbi *mipi)
{
	struct drm_device *drm = mipi->tinydrm.drm;
	u16 height = drm->mode_config.min_height;
	u16 width = drm->mode_config.min_width;
	size_t len = width * height * 2;

	memset(mipi->tx_buf, 0, len);

	mipi_dbi_command(mipi, MIPI_DCS_SET_COLUMN_ADDRESS, 0, 0,
			 (width >> 8) & 0xFF, (width - 1) & 0xFF);
	mipi_dbi_command(mipi, MIPI_DCS_SET_PAGE_ADDRESS, 0, 0,
			 (height >> 8) & 0xFF, (height - 1) & 0xFF);
	mipi_dbi_command_buf(mipi, MIPI_DCS_WRITE_MEMORY_START,
			     (u8 *)mipi->tx_buf, len);
}