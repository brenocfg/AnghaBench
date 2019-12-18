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
 int /*<<< orphan*/  kempld_write8 (struct kempld_device_data*,scalar_t__,scalar_t__) ; 

void kempld_write16(struct kempld_device_data *pld, u8 index, u16 data)
{
	kempld_write8(pld, index, (u8)data);
	kempld_write8(pld, index + 1, (u8)(data >> 8));
}