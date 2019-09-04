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
struct sii8620 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_EDID_CTRL_EDID_PRIME_VALID ; 
 int /*<<< orphan*/  BIT_HPD_CTRL_HPD_OUT_OVR_EN ; 
 int /*<<< orphan*/  REG_EDID_CTRL ; 
 int /*<<< orphan*/  REG_HPD_CTRL ; 
 int /*<<< orphan*/  REG_INTR8_MASK ; 
 int /*<<< orphan*/  sii8620_setbits (struct sii8620*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_write_seq_static (struct sii8620*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sii8620_disable_hpd(struct sii8620 *ctx)
{
	sii8620_setbits(ctx, REG_EDID_CTRL, BIT_EDID_CTRL_EDID_PRIME_VALID, 0);
	sii8620_write_seq_static(ctx,
		REG_HPD_CTRL, BIT_HPD_CTRL_HPD_OUT_OVR_EN,
		REG_INTR8_MASK, 0
	);
}