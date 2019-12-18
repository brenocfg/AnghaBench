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
struct hl_device {int dummy; } ;
typedef  enum hl_device_hw_state { ____Placeholder_hl_device_hw_state } hl_device_hw_state ;

/* Variables and functions */
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmHW_STATE ; 

__attribute__((used)) static enum hl_device_hw_state goya_get_hw_state(struct hl_device *hdev)
{
	return RREG32(mmHW_STATE);
}