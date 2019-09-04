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
 int CRC_SIZES_SHIFT ; 
 int /*<<< orphan*/  GENERAL_CONFIG ; 
 int VAU_SHIFT ; 
 int VCU_SHIFT ; 
 int /*<<< orphan*/  VERIFY_CAP_LOCAL_FABRIC ; 
 int VL15BUF_SHIFT ; 
 int Z_SHIFT ; 
 int load_8051_config (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int write_vc_local_fabric(struct hfi1_devdata *dd, u8 vau, u8 z, u8 vcu,
				 u16 vl15buf, u8 crc_sizes)
{
	u32 frame;

	frame = (u32)vau << VAU_SHIFT
		| (u32)z << Z_SHIFT
		| (u32)vcu << VCU_SHIFT
		| (u32)vl15buf << VL15BUF_SHIFT
		| (u32)crc_sizes << CRC_SIZES_SHIFT;
	return load_8051_config(dd, VERIFY_CAP_LOCAL_FABRIC,
				GENERAL_CONFIG, frame);
}