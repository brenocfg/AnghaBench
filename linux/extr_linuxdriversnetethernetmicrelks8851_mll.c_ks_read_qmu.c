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
typedef  int /*<<< orphan*/  u16 ;
struct ks_net {int extra_byte; int rc_rxqcr; int /*<<< orphan*/  hw_addr; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  KS_RXFDPR ; 
 int /*<<< orphan*/  KS_RXQCR ; 
 int /*<<< orphan*/  RXFDPR_RXFPAI ; 
 int RXQCR_SDA ; 
 int /*<<< orphan*/  ioread8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_inblk (struct ks_net*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ks_wrreg16 (struct ks_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_wrreg8 (struct ks_net*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void ks_read_qmu(struct ks_net *ks, u16 *buf, u32 len)
{
	u32 r =  ks->extra_byte & 0x1 ;
	u32 w = ks->extra_byte - r;

	/* 1. set sudo DMA mode */
	ks_wrreg16(ks, KS_RXFDPR, RXFDPR_RXFPAI);
	ks_wrreg8(ks, KS_RXQCR, (ks->rc_rxqcr | RXQCR_SDA) & 0xff);

	/* 2. read prepend data */
	/**
	 * read 4 + extra bytes and discard them.
	 * extra bytes for dummy, 2 for status, 2 for len
	 */

	/* use likely(r) for 8 bit access for performance */
	if (unlikely(r))
		ioread8(ks->hw_addr);
	ks_inblk(ks, buf, w + 2 + 2);

	/* 3. read pkt data */
	ks_inblk(ks, buf, ALIGN(len, 4));

	/* 4. reset sudo DMA Mode */
	ks_wrreg8(ks, KS_RXQCR, ks->rc_rxqcr);
}