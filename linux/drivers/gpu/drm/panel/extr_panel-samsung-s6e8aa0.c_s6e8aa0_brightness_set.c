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
typedef  int /*<<< orphan*/  u8 ;
struct s6e8aa0 {size_t brightness; int version; TYPE_1__* variant; scalar_t__ error; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** gamma_tables; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAMMA_TABLE_LEN ; 
 int /*<<< orphan*/  s6e8aa0_dcs_write (struct s6e8aa0*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s6e8aa0_dcs_write_seq_static (struct s6e8aa0*,int,int) ; 
 int /*<<< orphan*/  s6e8aa0_elvss_nvm_set (struct s6e8aa0*) ; 

__attribute__((used)) static void s6e8aa0_brightness_set(struct s6e8aa0 *ctx)
{
	const u8 *gamma;

	if (ctx->error)
		return;

	gamma = ctx->variant->gamma_tables[ctx->brightness];

	if (ctx->version >= 142)
		s6e8aa0_elvss_nvm_set(ctx);

	s6e8aa0_dcs_write(ctx, gamma, GAMMA_TABLE_LEN);

	/* update gamma table. */
	s6e8aa0_dcs_write_seq_static(ctx, 0xf7, 0x03);
}