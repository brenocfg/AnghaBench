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
 int /*<<< orphan*/  process_ext_display_connection_info (struct bios_parser*) ; 

__attribute__((used)) static void bios_parser_post_init(struct dc_bios *dcb)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);

	process_ext_display_connection_info(bp);
}