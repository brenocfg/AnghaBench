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
 int LINK_WIDTH_SHIFT ; 
 int LOCAL_FLAG_BITS_SHIFT ; 
 int MISC_CONFIG_BITS_SHIFT ; 
 int /*<<< orphan*/  VERIFY_CAP_LOCAL_LINK_MODE ; 
 int load_8051_config (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int write_vc_local_link_mode(struct hfi1_devdata *dd,
				    u8 misc_bits,
				    u8 flag_bits,
				    u16 link_widths)
{
	u32 frame;

	frame = (u32)misc_bits << MISC_CONFIG_BITS_SHIFT
		| (u32)flag_bits << LOCAL_FLAG_BITS_SHIFT
		| (u32)link_widths << LINK_WIDTH_SHIFT;
	return load_8051_config(dd, VERIFY_CAP_LOCAL_LINK_MODE, GENERAL_CONFIG,
		     frame);
}