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
typedef  int u8 ;

/* Variables and functions */
#define  TQMX86_REG_BOARD_ID_50UC 137 
#define  TQMX86_REG_BOARD_ID_60EB 136 
#define  TQMX86_REG_BOARD_ID_70EB 135 
#define  TQMX86_REG_BOARD_ID_80UC 134 
#define  TQMX86_REG_BOARD_ID_90UC 133 
#define  TQMX86_REG_BOARD_ID_E38C 132 
#define  TQMX86_REG_BOARD_ID_E38M 131 
#define  TQMX86_REG_BOARD_ID_E39C 130 
#define  TQMX86_REG_BOARD_ID_E39M 129 
#define  TQMX86_REG_BOARD_ID_E39x 128 

__attribute__((used)) static int tqmx86_board_id_to_clk_rate(u8 board_id)
{
	switch (board_id) {
	case TQMX86_REG_BOARD_ID_50UC:
	case TQMX86_REG_BOARD_ID_60EB:
	case TQMX86_REG_BOARD_ID_70EB:
	case TQMX86_REG_BOARD_ID_80UC:
	case TQMX86_REG_BOARD_ID_90UC:
		return 24000;
	case TQMX86_REG_BOARD_ID_E39M:
	case TQMX86_REG_BOARD_ID_E39C:
	case TQMX86_REG_BOARD_ID_E39x:
		return 25000;
	case TQMX86_REG_BOARD_ID_E38M:
	case TQMX86_REG_BOARD_ID_E38C:
		return 33000;
	default:
		return 0;
	}
}