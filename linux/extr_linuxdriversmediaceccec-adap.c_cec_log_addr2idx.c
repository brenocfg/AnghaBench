#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int num_log_addrs; scalar_t__* log_addr; } ;
struct cec_adapter {TYPE_1__ log_addrs; } ;

/* Variables and functions */

__attribute__((used)) static int cec_log_addr2idx(const struct cec_adapter *adap, u8 log_addr)
{
	int i;

	for (i = 0; i < adap->log_addrs.num_log_addrs; i++)
		if (adap->log_addrs.log_addr[i] == log_addr)
			return i;
	return -1;
}