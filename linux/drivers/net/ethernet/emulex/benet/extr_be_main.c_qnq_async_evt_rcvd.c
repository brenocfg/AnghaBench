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
struct be_adapter {int flags; } ;

/* Variables and functions */
 int BE_FLAGS_QNQ_ASYNC_EVT_RCVD ; 

__attribute__((used)) static inline int qnq_async_evt_rcvd(struct be_adapter *adapter)
{
	return adapter->flags & BE_FLAGS_QNQ_ASYNC_EVT_RCVD;
}