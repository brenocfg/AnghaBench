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
struct komeda_component {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_CONTROL ; 
 int /*<<< orphan*/  BLK_INPUT_ID0 ; 
 int /*<<< orphan*/  L_EN ; 
 int /*<<< orphan*/  malidp_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_write32_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d71_wb_layer_disable(struct komeda_component *c)
{
	malidp_write32(c->reg, BLK_INPUT_ID0, 0);
	malidp_write32_mask(c->reg, BLK_CONTROL, L_EN, 0);
}