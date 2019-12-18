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
struct tps6598x_rx_identity_reg {int /*<<< orphan*/  identity; } ;
struct tps6598x {int /*<<< orphan*/  partner_identity; } ;
typedef  int /*<<< orphan*/  id ;

/* Variables and functions */
 int /*<<< orphan*/  TPS_REG_RX_IDENTITY_SOP ; 
 int tps6598x_block_read (struct tps6598x*,int /*<<< orphan*/ ,struct tps6598x_rx_identity_reg*,int) ; 

__attribute__((used)) static int tps6598x_read_partner_identity(struct tps6598x *tps)
{
	struct tps6598x_rx_identity_reg id;
	int ret;

	ret = tps6598x_block_read(tps, TPS_REG_RX_IDENTITY_SOP,
				  &id, sizeof(id));
	if (ret)
		return ret;

	tps->partner_identity = id.identity;

	return 0;
}