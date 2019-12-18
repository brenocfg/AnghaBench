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
struct ssb_pcicore {int dummy; } ;

/* Variables and functions */
 int ssb_pcie_read (struct ssb_pcicore*,int) ; 

__attribute__((used)) static u8 ssb_pcicore_polarity_workaround(struct ssb_pcicore *pc)
{
	return (ssb_pcie_read(pc, 0x204) & 0x10) ? 0xC0 : 0x80;
}