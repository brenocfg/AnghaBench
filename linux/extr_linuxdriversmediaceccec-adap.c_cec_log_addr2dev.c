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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {unsigned int* primary_device_type; } ;
struct cec_adapter {TYPE_1__ log_addrs; } ;

/* Variables and functions */
 int cec_log_addr2idx (struct cec_adapter const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int cec_log_addr2dev(const struct cec_adapter *adap, u8 log_addr)
{
	int i = cec_log_addr2idx(adap, log_addr);

	return adap->log_addrs.primary_device_type[i < 0 ? 0 : i];
}