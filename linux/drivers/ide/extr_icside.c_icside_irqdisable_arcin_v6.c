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
struct icside_state {scalar_t__ irq_port; scalar_t__ enabled; } ;
struct expansion_card {struct icside_state* irq_data; } ;

/* Variables and functions */
 scalar_t__ ICS_ARCIN_V6_INTROFFSET_1 ; 
 scalar_t__ ICS_ARCIN_V6_INTROFFSET_2 ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 

__attribute__((used)) static void icside_irqdisable_arcin_v6 (struct expansion_card *ec, int irqnr)
{
	struct icside_state *state = ec->irq_data;

	state->enabled = 0;

	readb(state->irq_port + ICS_ARCIN_V6_INTROFFSET_1);
	readb(state->irq_port + ICS_ARCIN_V6_INTROFFSET_2);
}