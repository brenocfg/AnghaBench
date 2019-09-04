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
struct mtk_dpi_sync_param {int sync_width; int back_porch; int front_porch; } ;
struct mtk_dpi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPI_TGEN_HPORCH ; 
 int /*<<< orphan*/  DPI_TGEN_HWIDTH ; 
 int HBP ; 
 int /*<<< orphan*/  HBP_MASK ; 
 int HFP ; 
 int /*<<< orphan*/  HFP_MASK ; 
 int HPW ; 
 int /*<<< orphan*/  HPW_MASK ; 
 int /*<<< orphan*/  mtk_dpi_mask (struct mtk_dpi*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_dpi_config_hsync(struct mtk_dpi *dpi,
				 struct mtk_dpi_sync_param *sync)
{
	mtk_dpi_mask(dpi, DPI_TGEN_HWIDTH,
		     sync->sync_width << HPW, HPW_MASK);
	mtk_dpi_mask(dpi, DPI_TGEN_HPORCH,
		     sync->back_porch << HBP, HBP_MASK);
	mtk_dpi_mask(dpi, DPI_TGEN_HPORCH, sync->front_porch << HFP,
		     HFP_MASK);
}