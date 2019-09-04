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
typedef  int /*<<< orphan*/  u32 ;
struct fritz_adapter {scalar_t__ io; } ;

/* Variables and functions */
 int AVM_HDLC_STATUS_1 ; 
 int AVM_HDLC_STATUS_2 ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 

__attribute__((used)) static u32 fcpci2_read_hdlc_status(struct fritz_adapter *adapter, int nr)
{
	int offset = nr ? AVM_HDLC_STATUS_2 : AVM_HDLC_STATUS_1;

	return inl(adapter->io + offset);
}