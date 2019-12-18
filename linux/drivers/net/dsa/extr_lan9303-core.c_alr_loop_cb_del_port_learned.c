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
struct lan9303 {int dummy; } ;
struct del_port_learned_ctx {int port; } ;

/* Variables and functions */
 int BIT (int) ; 
 int LAN9303_ALR_DAT1_STATIC ; 
 int LAN9303_ALR_DAT1_VALID ; 
 int /*<<< orphan*/  lan9303_alr_make_entry_raw (struct lan9303*,int,int) ; 

__attribute__((used)) static void alr_loop_cb_del_port_learned(struct lan9303 *chip, u32 dat0,
					 u32 dat1, int portmap, void *ctx)
{
	struct del_port_learned_ctx *del_ctx = ctx;
	int port = del_ctx->port;

	if (((BIT(port) & portmap) == 0) || (dat1 & LAN9303_ALR_DAT1_STATIC))
		return;

	/* learned entries has only one port, we can just delete */
	dat1 &= ~LAN9303_ALR_DAT1_VALID; /* delete entry */
	lan9303_alr_make_entry_raw(chip, dat0, dat1);
}