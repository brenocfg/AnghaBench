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
 int EIO ; 
 int SLIPORT_READY_TIMEOUT ; 
 int SLIPORT_STATUS_ERR_MASK ; 
 scalar_t__ SLIPORT_STATUS_OFFSET ; 
 int SLIPORT_STATUS_RDY_MASK ; 
 int SLIPORT_STATUS_RN_MASK ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int lancer_wait_ready(struct be_adapter *adapter)
{
#define SLIPORT_READY_TIMEOUT 30
	u32 sliport_status;
	int i;

	for (i = 0; i < SLIPORT_READY_TIMEOUT; i++) {
		sliport_status = ioread32(adapter->db + SLIPORT_STATUS_OFFSET);
		if (sliport_status & SLIPORT_STATUS_RDY_MASK)
			return 0;

		if (sliport_status & SLIPORT_STATUS_ERR_MASK &&
		    !(sliport_status & SLIPORT_STATUS_RN_MASK))
			return -EIO;

		msleep(1000);
	}

	return sliport_status ? : -1;
}