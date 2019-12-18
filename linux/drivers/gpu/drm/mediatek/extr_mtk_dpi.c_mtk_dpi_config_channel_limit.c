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
struct mtk_dpi_yc_limit {int y_bottom; int y_top; int c_bottom; int c_top; } ;
struct mtk_dpi {int dummy; } ;

/* Variables and functions */
 int C_LIMIT_BOT ; 
 int /*<<< orphan*/  C_LIMIT_BOT_MASK ; 
 int C_LIMIT_TOP ; 
 int /*<<< orphan*/  C_LIMIT_TOP_MASK ; 
 int /*<<< orphan*/  DPI_C_LIMIT ; 
 int /*<<< orphan*/  DPI_Y_LIMIT ; 
 int Y_LIMINT_BOT ; 
 int /*<<< orphan*/  Y_LIMINT_BOT_MASK ; 
 int Y_LIMINT_TOP ; 
 int /*<<< orphan*/  Y_LIMINT_TOP_MASK ; 
 int /*<<< orphan*/  mtk_dpi_mask (struct mtk_dpi*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_dpi_config_channel_limit(struct mtk_dpi *dpi,
					 struct mtk_dpi_yc_limit *limit)
{
	mtk_dpi_mask(dpi, DPI_Y_LIMIT, limit->y_bottom << Y_LIMINT_BOT,
		     Y_LIMINT_BOT_MASK);
	mtk_dpi_mask(dpi, DPI_Y_LIMIT, limit->y_top << Y_LIMINT_TOP,
		     Y_LIMINT_TOP_MASK);
	mtk_dpi_mask(dpi, DPI_C_LIMIT, limit->c_bottom << C_LIMIT_BOT,
		     C_LIMIT_BOT_MASK);
	mtk_dpi_mask(dpi, DPI_C_LIMIT, limit->c_top << C_LIMIT_TOP,
		     C_LIMIT_TOP_MASK);
}