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
struct mtk_dpi_sync_param {int dummy; } ;
struct mtk_dpi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPI_TGEN_VPORCH ; 
 int /*<<< orphan*/  DPI_TGEN_VWIDTH ; 
 int /*<<< orphan*/  mtk_dpi_config_vsync (struct mtk_dpi*,struct mtk_dpi_sync_param*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_dpi_config_vsync_lodd(struct mtk_dpi *dpi,
				      struct mtk_dpi_sync_param *sync)
{
	mtk_dpi_config_vsync(dpi, sync, DPI_TGEN_VWIDTH, DPI_TGEN_VPORCH);
}