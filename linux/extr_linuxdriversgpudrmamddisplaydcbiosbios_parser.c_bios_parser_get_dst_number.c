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
typedef  int /*<<< orphan*/  uint32_t ;
struct graphics_object_id {int dummy; } ;
struct dc_bios {int dummy; } ;
struct bios_parser {int dummy; } ;
typedef  int /*<<< orphan*/  ATOM_OBJECT ;

/* Variables and functions */
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 int /*<<< orphan*/ * get_bios_object (struct bios_parser*,struct graphics_object_id) ; 
 int /*<<< orphan*/  get_dst_number_from_object (struct bios_parser*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t bios_parser_get_dst_number(struct dc_bios *dcb,
	struct graphics_object_id id)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);
	ATOM_OBJECT *object = get_bios_object(bp, id);

	return get_dst_number_from_object(bp, object);
}