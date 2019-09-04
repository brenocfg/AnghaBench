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
struct hfi1_devdata {int revision; } ;

/* Variables and functions */
 int CCE_REVISION_CHIP_REV_MINOR_MASK ; 
 int CCE_REVISION_CHIP_REV_MINOR_SHIFT ; 

int is_ax(struct hfi1_devdata *dd)
{
	u8 chip_rev_minor =
		dd->revision >> CCE_REVISION_CHIP_REV_MINOR_SHIFT
			& CCE_REVISION_CHIP_REV_MINOR_MASK;
	return (chip_rev_minor & 0xf0) == 0;
}