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
struct vmxnet3_tx_queue {int stopped; } ;
struct vmxnet3_adapter {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool
vmxnet3_tq_stopped(struct vmxnet3_tx_queue *tq, struct vmxnet3_adapter *adapter)
{
	return tq->stopped;
}