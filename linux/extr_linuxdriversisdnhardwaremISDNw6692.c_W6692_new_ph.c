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
struct w6692_hw {scalar_t__ state; int /*<<< orphan*/  dch; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_PHCHANGE ; 
 int /*<<< orphan*/  W_L1CMD_DRC ; 
 scalar_t__ W_L1CMD_RST ; 
 int /*<<< orphan*/  ph_command (struct w6692_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
W6692_new_ph(struct w6692_hw *card)
{
	if (card->state == W_L1CMD_RST)
		ph_command(card, W_L1CMD_DRC);
	schedule_event(&card->dch, FLG_PHCHANGE);
}