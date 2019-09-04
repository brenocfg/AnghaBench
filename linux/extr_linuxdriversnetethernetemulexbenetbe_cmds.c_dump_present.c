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
struct be_adapter {scalar_t__ db; } ;

/* Variables and functions */
 int SLIPORT_STATUS_DIP_MASK ; 
 scalar_t__ SLIPORT_STATUS_OFFSET ; 
 int ioread32 (scalar_t__) ; 

bool dump_present(struct be_adapter *adapter)
{
	u32 sliport_status = 0;

	sliport_status = ioread32(adapter->db + SLIPORT_STATUS_OFFSET);
	return !!(sliport_status & SLIPORT_STATUS_DIP_MASK);
}