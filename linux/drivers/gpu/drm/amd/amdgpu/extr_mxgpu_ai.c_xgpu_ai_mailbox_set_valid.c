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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AI_MAIBOX_CONTROL_TRN_OFFSET_BYTE ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgpu_ai_mailbox_set_valid(struct amdgpu_device *adev, bool val)
{
	WREG8(AI_MAIBOX_CONTROL_TRN_OFFSET_BYTE, val ? 1 : 0);
}