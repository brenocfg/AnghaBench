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
typedef  int /*<<< orphan*/  u8 ;
struct w6692_hw {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  W_CIX ; 
 int /*<<< orphan*/  WriteW6692 (struct w6692_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ph_command(struct w6692_hw *card, u8 cmd)
{
	pr_debug("%s: ph_command %x\n", card->name, cmd);
	WriteW6692(card, W_CIX, cmd);
}