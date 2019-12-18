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
struct dc_bios {int dummy; } ;
struct bios_parser {int dummy; } ;

/* Variables and functions */
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  destruct (struct bios_parser*) ; 
 int /*<<< orphan*/  kfree (struct bios_parser*) ; 

__attribute__((used)) static void bios_parser_destroy(struct dc_bios **dcb)
{
	struct bios_parser *bp = BP_FROM_DCB(*dcb);

	if (!bp) {
		BREAK_TO_DEBUGGER();
		return;
	}

	destruct(bp);

	kfree(bp);
	*dcb = NULL;
}