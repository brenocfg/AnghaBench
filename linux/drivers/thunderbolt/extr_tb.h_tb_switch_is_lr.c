#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ device_id; } ;
struct tb_switch {TYPE_1__ config; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_INTEL_LIGHT_RIDGE ; 

__attribute__((used)) static inline bool tb_switch_is_lr(const struct tb_switch *sw)
{
	return sw->config.device_id == PCI_DEVICE_ID_INTEL_LIGHT_RIDGE;
}