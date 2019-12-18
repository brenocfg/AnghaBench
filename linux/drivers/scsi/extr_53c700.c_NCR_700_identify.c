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
typedef  int __u8 ;

/* Variables and functions */
 int IDENTIFY_BASE ; 
 int NCR_700_LUN_MASK ; 

__attribute__((used)) static inline __u8
NCR_700_identify(int can_disconnect, __u8 lun)
{
	return IDENTIFY_BASE |
		((can_disconnect) ? 0x40 : 0) |
		(lun & NCR_700_LUN_MASK);
}