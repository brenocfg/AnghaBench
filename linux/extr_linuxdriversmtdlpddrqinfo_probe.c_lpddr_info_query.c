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
typedef  unsigned int uint16_t ;
struct map_info {scalar_t__ pfow_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD (unsigned long) ; 
 unsigned int CMDVAL (int /*<<< orphan*/ ) ; 
 unsigned int DSR_READY_STATUS ; 
 unsigned long LPDDR_INFO_QUERY ; 
 unsigned long LPDDR_START_EXECUTION ; 
 scalar_t__ PFOW_COMMAND_ADDRESS_H ; 
 scalar_t__ PFOW_COMMAND_ADDRESS_L ; 
 scalar_t__ PFOW_COMMAND_CODE ; 
 scalar_t__ PFOW_COMMAND_DATA ; 
 scalar_t__ PFOW_COMMAND_EXECUTE ; 
 scalar_t__ PFOW_DSR ; 
 unsigned long lpddr_get_qinforec_pos (struct map_info*,char*) ; 
 int map_bankwidth (struct map_info*) ; 
 int /*<<< orphan*/  map_read (struct map_info*,scalar_t__) ; 
 int /*<<< orphan*/  map_write (struct map_info*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static uint16_t lpddr_info_query(struct map_info *map, char *id_str)
{
	unsigned int dsr, val;
	int bits_per_chip = map_bankwidth(map) * 8;
	unsigned long adr = lpddr_get_qinforec_pos(map, id_str);
	int attempts = 20;

	/* Write a request for the PFOW record */
	map_write(map, CMD(LPDDR_INFO_QUERY),
			map->pfow_base + PFOW_COMMAND_CODE);
	map_write(map, CMD(adr & ((1 << bits_per_chip) - 1)),
			map->pfow_base + PFOW_COMMAND_ADDRESS_L);
	map_write(map, CMD(adr >> bits_per_chip),
			map->pfow_base + PFOW_COMMAND_ADDRESS_H);
	map_write(map, CMD(LPDDR_START_EXECUTION),
			map->pfow_base + PFOW_COMMAND_EXECUTE);

	while ((attempts--) > 0) {
		dsr = CMDVAL(map_read(map, map->pfow_base + PFOW_DSR));
		if (dsr & DSR_READY_STATUS)
			break;
		udelay(10);
	}

	val = CMDVAL(map_read(map, map->pfow_base + PFOW_COMMAND_DATA));
	return val;
}