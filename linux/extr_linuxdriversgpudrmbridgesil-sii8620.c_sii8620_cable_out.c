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
struct sii8620 {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_hw_off (struct sii8620*) ; 
 TYPE_1__* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sii8620_cable_out(struct sii8620 *ctx)
{
	disable_irq(to_i2c_client(ctx->dev)->irq);
	sii8620_hw_off(ctx);
}