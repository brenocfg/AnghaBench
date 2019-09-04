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
struct w6692_hw {int /*<<< orphan*/  imask; } ;

/* Variables and functions */
 int /*<<< orphan*/  W_IMASK ; 
 int /*<<< orphan*/  WriteW6692 (struct w6692_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
enable_hwirq(struct w6692_hw *card)
{
	WriteW6692(card, W_IMASK, card->imask);
}