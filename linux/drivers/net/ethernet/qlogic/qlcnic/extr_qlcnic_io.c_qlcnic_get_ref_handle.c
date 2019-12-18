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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 

__attribute__((used)) static inline u32 qlcnic_get_ref_handle(struct qlcnic_adapter *adapter,
					u16 handle, u8 ring_id)
{
	if (qlcnic_83xx_check(adapter))
		return handle | (ring_id << 15);
	else
		return handle;
}