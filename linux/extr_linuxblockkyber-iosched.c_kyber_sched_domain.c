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

/* Variables and functions */
 unsigned int KYBER_OTHER ; 
 unsigned int KYBER_READ ; 
 unsigned int KYBER_SYNC_WRITE ; 
 unsigned int REQ_OP_MASK ; 
 unsigned int REQ_OP_READ ; 
 unsigned int REQ_OP_WRITE ; 
 scalar_t__ op_is_sync (unsigned int) ; 

__attribute__((used)) static unsigned int kyber_sched_domain(unsigned int op)
{
	if ((op & REQ_OP_MASK) == REQ_OP_READ)
		return KYBER_READ;
	else if ((op & REQ_OP_MASK) == REQ_OP_WRITE && op_is_sync(op))
		return KYBER_SYNC_WRITE;
	else
		return KYBER_OTHER;
}