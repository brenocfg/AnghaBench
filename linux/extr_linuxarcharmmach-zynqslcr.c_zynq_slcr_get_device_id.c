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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SLCR_PSS_IDCODE ; 
 int SLCR_PSS_IDCODE_DEVICE_MASK ; 
 int SLCR_PSS_IDCODE_DEVICE_SHIFT ; 
 int /*<<< orphan*/  zynq_slcr_read (int*,int /*<<< orphan*/ ) ; 

u32 zynq_slcr_get_device_id(void)
{
	u32 val;

	zynq_slcr_read(&val, SLCR_PSS_IDCODE);
	val >>= SLCR_PSS_IDCODE_DEVICE_SHIFT;
	val &= SLCR_PSS_IDCODE_DEVICE_MASK;

	return val;
}