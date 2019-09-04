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
struct ld9040 {size_t brightness; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCS_GAMMA_CTRL ; 
 int /*<<< orphan*/  ld9040_dcs_write (struct ld9040*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ld9040_dcs_write_seq_static (struct ld9040*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * ld9040_gammas ; 

__attribute__((used)) static void ld9040_brightness_set(struct ld9040 *ctx)
{
	ld9040_dcs_write(ctx, ld9040_gammas[ctx->brightness],
			 ARRAY_SIZE(ld9040_gammas[ctx->brightness]));

	ld9040_dcs_write_seq_static(ctx, MCS_GAMMA_CTRL, 0x02, 0x5a);
}