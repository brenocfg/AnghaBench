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
typedef  int u32 ;
struct spi_nor {int addr_width; int read_dummy; int read_opcode; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int const* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SMPT_CMD_OPCODE (int const) ; 
 int SMPT_CMD_READ_DATA (int const) ; 
 int const SMPT_DESC_END ; 
 int const SMPT_DESC_TYPE_MAP ; 
 int SMPT_MAP_ID (int const) ; 
 scalar_t__ SMPT_MAP_REGION_COUNT (int const) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int spi_nor_read_raw (struct spi_nor*,int,int,int*) ; 
 int spi_nor_smpt_addr_width (struct spi_nor*,int const) ; 
 int spi_nor_smpt_read_dummy (struct spi_nor*,int const) ; 

__attribute__((used)) static const u32 *spi_nor_get_map_in_use(struct spi_nor *nor, const u32 *smpt,
					 u8 smpt_len)
{
	const u32 *ret;
	u8 *buf;
	u32 addr;
	int err;
	u8 i;
	u8 addr_width, read_opcode, read_dummy;
	u8 read_data_mask, map_id;

	/* Use a kmalloc'ed bounce buffer to guarantee it is DMA-able. */
	buf = kmalloc(sizeof(*buf), GFP_KERNEL);
	if (!buf)
		return ERR_PTR(-ENOMEM);

	addr_width = nor->addr_width;
	read_dummy = nor->read_dummy;
	read_opcode = nor->read_opcode;

	map_id = 0;
	/* Determine if there are any optional Detection Command Descriptors */
	for (i = 0; i < smpt_len; i += 2) {
		if (smpt[i] & SMPT_DESC_TYPE_MAP)
			break;

		read_data_mask = SMPT_CMD_READ_DATA(smpt[i]);
		nor->addr_width = spi_nor_smpt_addr_width(nor, smpt[i]);
		nor->read_dummy = spi_nor_smpt_read_dummy(nor, smpt[i]);
		nor->read_opcode = SMPT_CMD_OPCODE(smpt[i]);
		addr = smpt[i + 1];

		err = spi_nor_read_raw(nor, addr, 1, buf);
		if (err) {
			ret = ERR_PTR(err);
			goto out;
		}

		/*
		 * Build an index value that is used to select the Sector Map
		 * Configuration that is currently in use.
		 */
		map_id = map_id << 1 | !!(*buf & read_data_mask);
	}

	/*
	 * If command descriptors are provided, they always precede map
	 * descriptors in the table. There is no need to start the iteration
	 * over smpt array all over again.
	 *
	 * Find the matching configuration map.
	 */
	ret = ERR_PTR(-EINVAL);
	while (i < smpt_len) {
		if (SMPT_MAP_ID(smpt[i]) == map_id) {
			ret = smpt + i;
			break;
		}

		/*
		 * If there are no more configuration map descriptors and no
		 * configuration ID matched the configuration identifier, the
		 * sector address map is unknown.
		 */
		if (smpt[i] & SMPT_DESC_END)
			break;

		/* increment the table index to the next map */
		i += SMPT_MAP_REGION_COUNT(smpt[i]) + 1;
	}

	/* fall through */
out:
	kfree(buf);
	nor->addr_width = addr_width;
	nor->read_dummy = read_dummy;
	nor->read_opcode = read_opcode;
	return ret;
}