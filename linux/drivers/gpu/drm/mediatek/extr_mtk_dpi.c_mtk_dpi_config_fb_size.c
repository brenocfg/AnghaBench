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
typedef  int u32 ;
struct mtk_dpi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPI_SIZE ; 
 int HSIZE ; 
 int /*<<< orphan*/  HSIZE_MASK ; 
 int VSIZE ; 
 int /*<<< orphan*/  VSIZE_MASK ; 
 int /*<<< orphan*/  mtk_dpi_mask (struct mtk_dpi*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_dpi_config_fb_size(struct mtk_dpi *dpi, u32 width, u32 height)
{
	mtk_dpi_mask(dpi, DPI_SIZE, width << HSIZE, HSIZE_MASK);
	mtk_dpi_mask(dpi, DPI_SIZE, height << VSIZE, VSIZE_MASK);
}