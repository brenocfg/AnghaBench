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
struct mtk_dpi {TYPE_1__* conf; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_h_fre_con; scalar_t__ edge_sel_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDGE_SEL_EN ; 
 int /*<<< orphan*/  mtk_dpi_mask (struct mtk_dpi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_dpi_config_disable_edge(struct mtk_dpi *dpi)
{
	if (dpi->conf->edge_sel_en)
		mtk_dpi_mask(dpi, dpi->conf->reg_h_fre_con, 0, EDGE_SEL_EN);
}