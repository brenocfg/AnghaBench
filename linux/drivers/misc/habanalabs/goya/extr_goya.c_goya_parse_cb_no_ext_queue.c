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
typedef  int /*<<< orphan*/  u64 ;
struct asic_fixed_properties {int /*<<< orphan*/  dram_end_address; int /*<<< orphan*/  dram_user_base_address; int /*<<< orphan*/  sram_end_address; int /*<<< orphan*/  sram_user_base_address; } ;
struct hl_device {int /*<<< orphan*/  dev; struct goya_device* asic_specific; struct asic_fixed_properties asic_prop; } ;
struct hl_cs_parser {int /*<<< orphan*/  user_cb_size; scalar_t__ user_cb; } ;
struct goya_device {int hw_cap_initialized; } ;

/* Variables and functions */
 int EFAULT ; 
 int HW_CAP_MMU ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ hl_mem_area_inside_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int goya_parse_cb_no_ext_queue(struct hl_device *hdev,
					struct hl_cs_parser *parser)
{
	struct asic_fixed_properties *asic_prop = &hdev->asic_prop;
	struct goya_device *goya = hdev->asic_specific;

	if (goya->hw_cap_initialized & HW_CAP_MMU)
		return 0;

	/* For internal queue jobs, just check if CB address is valid */
	if (hl_mem_area_inside_range(
			(u64) (uintptr_t) parser->user_cb,
			parser->user_cb_size,
			asic_prop->sram_user_base_address,
			asic_prop->sram_end_address))
		return 0;

	if (hl_mem_area_inside_range(
			(u64) (uintptr_t) parser->user_cb,
			parser->user_cb_size,
			asic_prop->dram_user_base_address,
			asic_prop->dram_end_address))
		return 0;

	dev_err(hdev->dev,
		"Internal CB address %px + 0x%x is not in SRAM nor in DRAM\n",
		parser->user_cb, parser->user_cb_size);

	return -EFAULT;
}