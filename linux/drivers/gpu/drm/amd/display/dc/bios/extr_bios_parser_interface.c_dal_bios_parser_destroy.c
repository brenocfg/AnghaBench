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
struct dc_bios {TYPE_1__* funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* bios_parser_destroy ) (struct dc_bios**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dc_bios**) ; 

void dal_bios_parser_destroy(struct dc_bios **dcb)
{
	struct dc_bios *bios = *dcb;

	bios->funcs->bios_parser_destroy(dcb);
}