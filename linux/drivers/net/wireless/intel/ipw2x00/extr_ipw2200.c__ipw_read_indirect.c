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
struct ipw_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_AUTOINC_ADDR ; 
 int /*<<< orphan*/  IPW_AUTOINC_DATA ; 
 int /*<<< orphan*/  IPW_DEBUG_IO (char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IPW_INDIRECT_ADDR ; 
 int IPW_INDIRECT_ADDR_MASK ; 
 scalar_t__ IPW_INDIRECT_DATA ; 
 int _ipw_read32 (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ipw_read8 (struct ipw_priv*,scalar_t__) ; 
 int /*<<< orphan*/  _ipw_write32 (struct ipw_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipw_read8 (struct ipw_priv*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void _ipw_read_indirect(struct ipw_priv *priv, u32 addr, u8 * buf,
			       int num)
{
	u32 aligned_addr = addr & IPW_INDIRECT_ADDR_MASK;	/* dword align */
	u32 dif_len = addr - aligned_addr;
	u32 i;

	IPW_DEBUG_IO("addr = %i, buf = %p, num = %i\n", addr, buf, num);

	if (num <= 0) {
		return;
	}

	/* Read the first dword (or portion) byte by byte */
	if (unlikely(dif_len)) {
		_ipw_write32(priv, IPW_INDIRECT_ADDR, aligned_addr);
		/* Start reading at aligned_addr + dif_len */
		for (i = dif_len; ((i < 4) && (num > 0)); i++, num--)
			*buf++ = _ipw_read8(priv, IPW_INDIRECT_DATA + i);
		aligned_addr += 4;
	}

	/* Read all of the middle dwords as dwords, with auto-increment */
	_ipw_write32(priv, IPW_AUTOINC_ADDR, aligned_addr);
	for (; num >= 4; buf += 4, aligned_addr += 4, num -= 4)
		*(u32 *) buf = _ipw_read32(priv, IPW_AUTOINC_DATA);

	/* Read the last dword (or portion) byte by byte */
	if (unlikely(num)) {
		_ipw_write32(priv, IPW_INDIRECT_ADDR, aligned_addr);
		for (i = 0; num > 0; i++, num--)
			*buf++ = ipw_read8(priv, IPW_INDIRECT_DATA + i);
	}
}