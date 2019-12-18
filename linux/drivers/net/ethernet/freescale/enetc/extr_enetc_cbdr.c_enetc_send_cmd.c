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
struct enetc_cbdr {int next_to_use; int bd_count; int /*<<< orphan*/  cir; int /*<<< orphan*/  pir; int /*<<< orphan*/  bd_base; } ;
struct enetc_si {struct enetc_cbdr cbd_ring; } ;
struct enetc_cbd {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 struct enetc_cbd* ENETC_CBD (struct enetc_cbdr,int) ; 
 int ENETC_CBDR_TIMEOUT ; 
 int /*<<< orphan*/  enetc_cbd_unused (struct enetc_cbdr*) ; 
 int /*<<< orphan*/  enetc_clean_cbdr (struct enetc_si*) ; 
 int enetc_rd_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_wr_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int enetc_send_cmd(struct enetc_si *si, struct enetc_cbd *cbd)
{
	struct enetc_cbdr *ring = &si->cbd_ring;
	int timeout = ENETC_CBDR_TIMEOUT;
	struct enetc_cbd *dest_cbd;
	int i;

	if (unlikely(!ring->bd_base))
		return -EIO;

	if (unlikely(!enetc_cbd_unused(ring)))
		enetc_clean_cbdr(si);

	i = ring->next_to_use;
	dest_cbd = ENETC_CBD(*ring, i);

	/* copy command to the ring */
	*dest_cbd = *cbd;
	i = (i + 1) % ring->bd_count;

	ring->next_to_use = i;
	/* let H/W know BD ring has been updated */
	enetc_wr_reg(ring->pir, i);

	do {
		if (enetc_rd_reg(ring->cir) == i)
			break;
		udelay(10); /* cannot sleep, rtnl_lock() */
		timeout -= 10;
	} while (timeout);

	if (!timeout)
		return -EBUSY;

	enetc_clean_cbdr(si);

	return 0;
}