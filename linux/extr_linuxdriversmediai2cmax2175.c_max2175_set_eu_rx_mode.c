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
struct max2175 {int /*<<< orphan*/  master; } ;

/* Variables and functions */
#define  MAX2175_DAB_1_2 129 
#define  MAX2175_EU_FM_1_2 128 
 int /*<<< orphan*/  max2175_load_dab_1p2 (struct max2175*) ; 
 int /*<<< orphan*/  max2175_load_fmeu_1p2 (struct max2175*) ; 
 int /*<<< orphan*/  max2175_write_bit (struct max2175*,int,int,int) ; 

__attribute__((used)) static void max2175_set_eu_rx_mode(struct max2175 *ctx, u32 rx_mode)
{
	switch (rx_mode) {
	case MAX2175_EU_FM_1_2:
		max2175_load_fmeu_1p2(ctx);
		break;

	case MAX2175_DAB_1_2:
		max2175_load_dab_1p2(ctx);
		break;
	}
	/* Master is the default setting */
	if (!ctx->master)
		max2175_write_bit(ctx, 30, 7, 1);
}