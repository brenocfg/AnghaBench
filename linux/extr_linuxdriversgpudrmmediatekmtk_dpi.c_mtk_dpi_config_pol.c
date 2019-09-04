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
struct mtk_dpi_polarities {scalar_t__ ck_pol; scalar_t__ de_pol; scalar_t__ hsync_pol; scalar_t__ vsync_pol; } ;
struct mtk_dpi {int dummy; } ;

/* Variables and functions */
 unsigned int CK_POL ; 
 unsigned int DE_POL ; 
 int /*<<< orphan*/  DPI_OUTPUT_SETTING ; 
 unsigned int HSYNC_POL ; 
 scalar_t__ MTK_DPI_POLARITY_RISING ; 
 unsigned int VSYNC_POL ; 
 int /*<<< orphan*/  mtk_dpi_mask (struct mtk_dpi*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void mtk_dpi_config_pol(struct mtk_dpi *dpi,
			       struct mtk_dpi_polarities *dpi_pol)
{
	unsigned int pol;

	pol = (dpi_pol->ck_pol == MTK_DPI_POLARITY_RISING ? 0 : CK_POL) |
	      (dpi_pol->de_pol == MTK_DPI_POLARITY_RISING ? 0 : DE_POL) |
	      (dpi_pol->hsync_pol == MTK_DPI_POLARITY_RISING ? 0 : HSYNC_POL) |
	      (dpi_pol->vsync_pol == MTK_DPI_POLARITY_RISING ? 0 : VSYNC_POL);
	mtk_dpi_mask(dpi, DPI_OUTPUT_SETTING, pol,
		     CK_POL | DE_POL | HSYNC_POL | VSYNC_POL);
}