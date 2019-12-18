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
struct lg_drv_data {int dummy; } ;
struct hid_usage {int dummy; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */

__attribute__((used)) static inline int lg4ff_adjust_input_event(struct hid_device *hid, struct hid_field *field,
					   struct hid_usage *usage, s32 value, struct lg_drv_data *drv_data) { return 0; }