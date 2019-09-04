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
typedef  int /*<<< orphan*/  u8 ;
struct cyapa {int dummy; } ;

/* Variables and functions */
 int CYAPA_FW_BLOCK_SIZE ; 
 int cyapa_gen3_write_fw_block (struct cyapa*,size_t,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int cyapa_gen3_write_blocks(struct cyapa *cyapa,
		size_t start_block, size_t block_count,
		const u8 *image_data)
{
	int error;
	int i;

	for (i = 0; i < block_count; i++) {
		size_t block = start_block + i;
		size_t addr = i * CYAPA_FW_BLOCK_SIZE;
		const u8 *data = &image_data[addr];

		error = cyapa_gen3_write_fw_block(cyapa, block, data);
		if (error)
			return error;
	}
	return 0;
}