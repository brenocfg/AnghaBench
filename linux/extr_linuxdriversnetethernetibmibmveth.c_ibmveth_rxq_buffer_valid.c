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
struct ibmveth_adapter {int dummy; } ;

/* Variables and functions */
 int IBMVETH_RXQ_VALID ; 
 int ibmveth_rxq_flags (struct ibmveth_adapter*) ; 

__attribute__((used)) static inline int ibmveth_rxq_buffer_valid(struct ibmveth_adapter *adapter)
{
	return ibmveth_rxq_flags(adapter) & IBMVETH_RXQ_VALID;
}