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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENERAL_CONFIG ; 
 int /*<<< orphan*/  LOCAL_DEVICE_ID ; 
 int LOCAL_DEVICE_ID_SHIFT ; 
 int LOCAL_DEVICE_REV_SHIFT ; 
 int load_8051_config (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int write_local_device_id(struct hfi1_devdata *dd, u16 device_id,
				 u8 device_rev)
{
	u32 frame;

	frame = ((u32)device_id << LOCAL_DEVICE_ID_SHIFT)
		| ((u32)device_rev << LOCAL_DEVICE_REV_SHIFT);
	return load_8051_config(dd, LOCAL_DEVICE_ID, GENERAL_CONFIG, frame);
}