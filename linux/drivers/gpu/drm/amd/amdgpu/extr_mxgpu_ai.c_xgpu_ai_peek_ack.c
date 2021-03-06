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
typedef  int uint8_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AI_MAIBOX_CONTROL_TRN_OFFSET_BYTE ; 
 int RREG8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t xgpu_ai_peek_ack(struct amdgpu_device *adev) {
	return RREG8(AI_MAIBOX_CONTROL_TRN_OFFSET_BYTE) & 2;
}