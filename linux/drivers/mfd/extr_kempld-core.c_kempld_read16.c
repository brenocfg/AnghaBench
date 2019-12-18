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
typedef  int u16 ;
struct kempld_device_data {int dummy; } ;

/* Variables and functions */
 int kempld_read8 (struct kempld_device_data*,scalar_t__) ; 

u16 kempld_read16(struct kempld_device_data *pld, u8 index)
{
	return kempld_read8(pld, index) | kempld_read8(pld, index + 1) << 8;
}