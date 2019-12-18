#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ val; } ;
struct TYPE_5__ {int /*<<< orphan*/ * in; } ;
struct TYPE_6__ {int nbytes; TYPE_2__ buf; } ;
struct spi_mem_op {TYPE_1__ addr; TYPE_3__ data; } ;
struct spi_mem {int dummy; } ;

/* Variables and functions */
 int npcm_fiu_uma_read (struct spi_mem*,struct spi_mem_op const*,scalar_t__,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int npcm_fiu_read(struct spi_mem *mem, const struct spi_mem_op *op)
{
	u8 *data = op->data.buf.in;
	int i, readlen, currlen;
	u8 *buf_ptr;
	u32 addr;
	int ret;

	i = 0;
	currlen = op->data.nbytes;

	do {
		addr = ((u32)op->addr.val + i);
		if (currlen < 16)
			readlen = currlen;
		else
			readlen = 16;

		buf_ptr = data + i;
		ret = npcm_fiu_uma_read(mem, op, addr, true, buf_ptr,
					readlen);
		if (ret)
			return ret;

		i += readlen;
		currlen -= 16;
	} while (currlen > 0);

	return 0;
}