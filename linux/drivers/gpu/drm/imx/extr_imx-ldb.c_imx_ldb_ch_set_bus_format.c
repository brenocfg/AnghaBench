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
struct imx_ldb_channel {int chno; struct imx_ldb* ldb; } ;
struct imx_ldb {int ldb_ctrl; } ;

/* Variables and functions */
 int LDB_BIT_MAP_CH0_JEIDA ; 
 int LDB_BIT_MAP_CH1_JEIDA ; 
 int LDB_DATA_WIDTH_CH0_24 ; 
 int LDB_DATA_WIDTH_CH1_24 ; 
 int LDB_SPLIT_MODE_EN ; 
#define  MEDIA_BUS_FMT_RGB666_1X7X3_SPWG 130 
#define  MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA 129 
#define  MEDIA_BUS_FMT_RGB888_1X7X4_SPWG 128 

__attribute__((used)) static void imx_ldb_ch_set_bus_format(struct imx_ldb_channel *imx_ldb_ch,
				      u32 bus_format)
{
	struct imx_ldb *ldb = imx_ldb_ch->ldb;
	int dual = ldb->ldb_ctrl & LDB_SPLIT_MODE_EN;

	switch (bus_format) {
	case MEDIA_BUS_FMT_RGB666_1X7X3_SPWG:
		break;
	case MEDIA_BUS_FMT_RGB888_1X7X4_SPWG:
		if (imx_ldb_ch->chno == 0 || dual)
			ldb->ldb_ctrl |= LDB_DATA_WIDTH_CH0_24;
		if (imx_ldb_ch->chno == 1 || dual)
			ldb->ldb_ctrl |= LDB_DATA_WIDTH_CH1_24;
		break;
	case MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA:
		if (imx_ldb_ch->chno == 0 || dual)
			ldb->ldb_ctrl |= LDB_DATA_WIDTH_CH0_24 |
					 LDB_BIT_MAP_CH0_JEIDA;
		if (imx_ldb_ch->chno == 1 || dual)
			ldb->ldb_ctrl |= LDB_DATA_WIDTH_CH1_24 |
					 LDB_BIT_MAP_CH1_JEIDA;
		break;
	}
}