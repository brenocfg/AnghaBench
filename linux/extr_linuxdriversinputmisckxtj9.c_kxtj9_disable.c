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
struct kxtj9_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kxtj9_device_power_off (struct kxtj9_data*) ; 

__attribute__((used)) static void kxtj9_disable(struct kxtj9_data *tj9)
{
	kxtj9_device_power_off(tj9);
}