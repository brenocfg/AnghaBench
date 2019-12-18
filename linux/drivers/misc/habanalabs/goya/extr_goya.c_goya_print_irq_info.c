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
typedef  int /*<<< orphan*/  u16 ;
struct hl_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  desc ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  goya_get_event_desc (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  goya_print_mmu_error_info (struct hl_device*) ; 
 int /*<<< orphan*/  goya_print_razwi_info (struct hl_device*) ; 

__attribute__((used)) static void goya_print_irq_info(struct hl_device *hdev, u16 event_type,
				bool razwi)
{
	char desc[20] = "";

	goya_get_event_desc(event_type, desc, sizeof(desc));
	dev_err(hdev->dev, "Received H/W interrupt %d [\"%s\"]\n",
		event_type, desc);

	if (razwi) {
		goya_print_razwi_info(hdev);
		goya_print_mmu_error_info(hdev);
	}
}