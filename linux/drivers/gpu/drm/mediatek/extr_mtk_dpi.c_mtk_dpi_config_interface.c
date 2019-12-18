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
struct mtk_dpi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPI_CON ; 
 int /*<<< orphan*/  INTL_EN ; 
 int /*<<< orphan*/  mtk_dpi_mask (struct mtk_dpi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_dpi_config_interface(struct mtk_dpi *dpi, bool inter)
{
	mtk_dpi_mask(dpi, DPI_CON, inter ? INTL_EN : 0, INTL_EN);
}