#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct enetc_cbdr {int next_to_clean; int bd_count; int /*<<< orphan*/  cir; } ;
struct enetc_si {TYPE_1__* pdev; struct enetc_cbdr cbd_ring; } ;
struct enetc_cbd {int status_flags; int /*<<< orphan*/  cmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct enetc_cbd* ENETC_CBD (struct enetc_cbdr,int) ; 
 int ENETC_CBD_STATUS_MASK ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int enetc_rd_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct enetc_cbd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enetc_clean_cbdr(struct enetc_si *si)
{
	struct enetc_cbdr *ring = &si->cbd_ring;
	struct enetc_cbd *dest_cbd;
	int i, status;

	i = ring->next_to_clean;

	while (enetc_rd_reg(ring->cir) != i) {
		dest_cbd = ENETC_CBD(*ring, i);
		status = dest_cbd->status_flags & ENETC_CBD_STATUS_MASK;
		if (status)
			dev_warn(&si->pdev->dev, "CMD err %04x for cmd %04x\n",
				 status, dest_cbd->cmd);

		memset(dest_cbd, 0, sizeof(*dest_cbd));

		i = (i + 1) % ring->bd_count;
	}

	ring->next_to_clean = i;
}