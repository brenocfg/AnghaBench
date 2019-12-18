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
typedef  int /*<<< orphan*/  u64 ;
struct enic {int /*<<< orphan*/  vdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RSS_CPU ; 
 int vnic_dev_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int enic_set_rss_cpu(struct enic *enic, dma_addr_t cpu_pa, u64 len)
{
	u64 a0 = (u64)cpu_pa, a1 = len;
	int wait = 1000;

	return vnic_dev_cmd(enic->vdev, CMD_RSS_CPU, &a0, &a1, wait);
}