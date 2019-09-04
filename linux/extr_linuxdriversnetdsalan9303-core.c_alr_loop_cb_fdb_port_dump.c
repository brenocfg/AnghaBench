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
struct port_fdb_dump_ctx {int /*<<< orphan*/  data; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  port; } ;
struct lan9303 {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ETH_ALEN ; 
 int LAN9303_ALR_DAT1_STATIC ; 
 int /*<<< orphan*/  alr_reg_to_mac (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alr_loop_cb_fdb_port_dump(struct lan9303 *chip, u32 dat0,
				      u32 dat1, int portmap, void *ctx)
{
	struct port_fdb_dump_ctx *dump_ctx = ctx;
	u8 mac[ETH_ALEN];
	bool is_static;

	if ((BIT(dump_ctx->port) & portmap) == 0)
		return;

	alr_reg_to_mac(dat0, dat1, mac);
	is_static = !!(dat1 & LAN9303_ALR_DAT1_STATIC);
	dump_ctx->cb(mac, 0, is_static, dump_ctx->data);
}