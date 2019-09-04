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
struct s6e8aa0 {int version; } ;

/* Variables and functions */
 int /*<<< orphan*/  s6e8aa0_dcs_write_seq_static (struct s6e8aa0*,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  s6e8aa0_elvss_nvm_set_v142 (struct s6e8aa0*) ; 

__attribute__((used)) static void s6e8aa0_elvss_nvm_set(struct s6e8aa0 *ctx)
{
	if (ctx->version < 142)
		s6e8aa0_dcs_write_seq_static(ctx,
			0xd9, 0x14, 0x40, 0x0c, 0xcb, 0xce, 0x6e, 0xc4, 0x07,
			0x40, 0x41, 0xc1, 0x00, 0x60, 0x19);
	else
		s6e8aa0_elvss_nvm_set_v142(ctx);
}