#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct device_id {int dummy; } ;
struct dc_bios {int dummy; } ;
struct TYPE_4__ {TYPE_1__* v1_1; } ;
struct bios_parser {TYPE_2__ object_info_tbl; } ;
struct TYPE_3__ {int /*<<< orphan*/  usDeviceSupport; } ;

/* Variables and functions */
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 int get_support_mask_for_device_id (struct device_id) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bios_parser_is_device_id_supported(
	struct dc_bios *dcb,
	struct device_id id)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);

	uint32_t mask = get_support_mask_for_device_id(id);

	return (le16_to_cpu(bp->object_info_tbl.v1_1->usDeviceSupport) & mask) != 0;
}