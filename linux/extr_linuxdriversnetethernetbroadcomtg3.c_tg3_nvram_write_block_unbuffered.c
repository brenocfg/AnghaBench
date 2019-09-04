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
typedef  int u32 ;
struct tg3 {int nvram_pagesize; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVRAM_ADDR ; 
 int NVRAM_CMD_DONE ; 
 int NVRAM_CMD_ERASE ; 
 int NVRAM_CMD_FIRST ; 
 int NVRAM_CMD_GO ; 
 int NVRAM_CMD_LAST ; 
 int NVRAM_CMD_WR ; 
 int NVRAM_CMD_WRDI ; 
 int NVRAM_CMD_WREN ; 
 int /*<<< orphan*/  NVRAM_WRDATA ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tg3_enable_nvram_access (struct tg3*) ; 
 int tg3_nvram_exec_cmd (struct tg3*,int) ; 
 int tg3_nvram_read_be32 (struct tg3*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tg3_nvram_write_block_unbuffered(struct tg3 *tp, u32 offset, u32 len,
		u8 *buf)
{
	int ret = 0;
	u32 pagesize = tp->nvram_pagesize;
	u32 pagemask = pagesize - 1;
	u32 nvram_cmd;
	u8 *tmp;

	tmp = kmalloc(pagesize, GFP_KERNEL);
	if (tmp == NULL)
		return -ENOMEM;

	while (len) {
		int j;
		u32 phy_addr, page_off, size;

		phy_addr = offset & ~pagemask;

		for (j = 0; j < pagesize; j += 4) {
			ret = tg3_nvram_read_be32(tp, phy_addr + j,
						  (__be32 *) (tmp + j));
			if (ret)
				break;
		}
		if (ret)
			break;

		page_off = offset & pagemask;
		size = pagesize;
		if (len < size)
			size = len;

		len -= size;

		memcpy(tmp + page_off, buf, size);

		offset = offset + (pagesize - page_off);

		tg3_enable_nvram_access(tp);

		/*
		 * Before we can erase the flash page, we need
		 * to issue a special "write enable" command.
		 */
		nvram_cmd = NVRAM_CMD_WREN | NVRAM_CMD_GO | NVRAM_CMD_DONE;

		if (tg3_nvram_exec_cmd(tp, nvram_cmd))
			break;

		/* Erase the target page */
		tw32(NVRAM_ADDR, phy_addr);

		nvram_cmd = NVRAM_CMD_GO | NVRAM_CMD_DONE | NVRAM_CMD_WR |
			NVRAM_CMD_FIRST | NVRAM_CMD_LAST | NVRAM_CMD_ERASE;

		if (tg3_nvram_exec_cmd(tp, nvram_cmd))
			break;

		/* Issue another write enable to start the write. */
		nvram_cmd = NVRAM_CMD_WREN | NVRAM_CMD_GO | NVRAM_CMD_DONE;

		if (tg3_nvram_exec_cmd(tp, nvram_cmd))
			break;

		for (j = 0; j < pagesize; j += 4) {
			__be32 data;

			data = *((__be32 *) (tmp + j));

			tw32(NVRAM_WRDATA, be32_to_cpu(data));

			tw32(NVRAM_ADDR, phy_addr + j);

			nvram_cmd = NVRAM_CMD_GO | NVRAM_CMD_DONE |
				NVRAM_CMD_WR;

			if (j == 0)
				nvram_cmd |= NVRAM_CMD_FIRST;
			else if (j == (pagesize - 4))
				nvram_cmd |= NVRAM_CMD_LAST;

			ret = tg3_nvram_exec_cmd(tp, nvram_cmd);
			if (ret)
				break;
		}
		if (ret)
			break;
	}

	nvram_cmd = NVRAM_CMD_WRDI | NVRAM_CMD_GO | NVRAM_CMD_DONE;
	tg3_nvram_exec_cmd(tp, nvram_cmd);

	kfree(tmp);

	return ret;
}