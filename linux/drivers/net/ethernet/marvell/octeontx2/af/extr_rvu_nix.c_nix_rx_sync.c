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
struct rvu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIX_AF_RX_SW_SYNC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_rvu_9xxx_A0 (struct rvu*) ; 
 int rvu_poll_reg (struct rvu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void nix_rx_sync(struct rvu *rvu, int blkaddr)
{
	int err;

	/*Sync all in flight RX packets to LLC/DRAM */
	rvu_write64(rvu, blkaddr, NIX_AF_RX_SW_SYNC, BIT_ULL(0));
	err = rvu_poll_reg(rvu, blkaddr, NIX_AF_RX_SW_SYNC, BIT_ULL(0), true);
	if (err)
		dev_err(rvu->dev, "NIX RX software sync failed\n");

	/* As per a HW errata in 9xxx A0 silicon, HW may clear SW_SYNC[ENA]
	 * bit too early. Hence wait for 50us more.
	 */
	if (is_rvu_9xxx_A0(rvu))
		usleep_range(50, 60);
}