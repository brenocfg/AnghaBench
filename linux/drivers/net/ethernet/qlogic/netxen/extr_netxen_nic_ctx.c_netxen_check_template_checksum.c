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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int* md_template; int md_template_size; } ;
struct netxen_adapter {TYPE_1__ mdump; } ;

/* Variables and functions */

__attribute__((used)) static u32
netxen_check_template_checksum(struct netxen_adapter *adapter)
{
	u64 sum =  0 ;
	u32 *buff = adapter->mdump.md_template;
	int count =  adapter->mdump.md_template_size/sizeof(uint32_t) ;

	while (count-- > 0)
		sum += *buff++ ;
	while (sum >> 32)
		sum = (sum & 0xFFFFFFFF) +  (sum >> 32) ;

	return ~sum;
}