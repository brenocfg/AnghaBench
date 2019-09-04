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
struct icside_state {scalar_t__ irq_port; } ;
struct expansion_card {struct icside_state* irq_data; } ;

/* Variables and functions */
 scalar_t__ ICS_ARCIN_V5_INTROFFSET ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void icside_irqenable_arcin_v5 (struct expansion_card *ec, int irqnr)
{
	struct icside_state *state = ec->irq_data;

	writeb(0, state->irq_port + ICS_ARCIN_V5_INTROFFSET);
}