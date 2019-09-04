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
typedef  int u64 ;
typedef  int u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_DC8051_STS_CUR_STATE ; 
 int DC_DC8051_STS_CUR_STATE_FIRMWARE_MASK ; 
 int DC_DC8051_STS_CUR_STATE_FIRMWARE_SHIFT ; 
 int read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 get_firmware_state(struct hfi1_devdata *dd)
{
	u64 reg = read_csr(dd, DC_DC8051_STS_CUR_STATE);

	return (reg >> DC_DC8051_STS_CUR_STATE_FIRMWARE_SHIFT)
				& DC_DC8051_STS_CUR_STATE_FIRMWARE_MASK;
}