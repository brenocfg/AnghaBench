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
struct venus_hfi_device {int state; int /*<<< orphan*/  lock; } ;
typedef  enum venus_state { ____Placeholder_venus_state } venus_state ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void venus_set_state(struct venus_hfi_device *hdev,
			    enum venus_state state)
{
	mutex_lock(&hdev->lock);
	hdev->state = state;
	mutex_unlock(&hdev->lock);
}