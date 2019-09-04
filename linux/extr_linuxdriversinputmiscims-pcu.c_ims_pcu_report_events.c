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
typedef  int u32 ;
struct ims_pcu {scalar_t__ gamepad; int /*<<< orphan*/ * read_buf; } ;

/* Variables and functions */
 int IMS_PCU_GAMEPAD_MASK ; 
 int get_unaligned_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ims_pcu_buttons_report (struct ims_pcu*,int) ; 
 int /*<<< orphan*/  ims_pcu_gamepad_report (struct ims_pcu*,int) ; 

__attribute__((used)) static void ims_pcu_report_events(struct ims_pcu *pcu)
{
	u32 data = get_unaligned_be32(&pcu->read_buf[3]);

	ims_pcu_buttons_report(pcu, data & ~IMS_PCU_GAMEPAD_MASK);
	if (pcu->gamepad)
		ims_pcu_gamepad_report(pcu, data);
}