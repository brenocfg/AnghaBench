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
struct venus_hfi_device {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ VENUS_STATE_DEINIT ; 

__attribute__((used)) static bool venus_is_valid_state(struct venus_hfi_device *hdev)
{
	return hdev->state != VENUS_STATE_DEINIT;
}