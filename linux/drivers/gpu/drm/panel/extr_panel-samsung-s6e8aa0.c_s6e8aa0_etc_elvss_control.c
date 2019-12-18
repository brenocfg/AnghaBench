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
typedef  int u8 ;
struct s6e8aa0 {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  s6e8aa0_dcs_write_seq (struct s6e8aa0*,int,int,int) ; 

__attribute__((used)) static void s6e8aa0_etc_elvss_control(struct s6e8aa0 *ctx)
{
	u8 id = ctx->id ? 0 : 0x95;

	s6e8aa0_dcs_write_seq(ctx, 0xb1, 0x04, id);
}