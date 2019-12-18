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
struct net_device {unsigned long base_addr; } ;

/* Variables and functions */
 unsigned long HYDRA_NIC_BASE ; 
 int NESM_START_PG ; 
 int /*<<< orphan*/  z_memcpy_toio (unsigned long,unsigned char const*,int) ; 

__attribute__((used)) static void hydra_block_output(struct net_device *dev, int count,
			       const unsigned char *buf, int start_page)
{
    unsigned long nic_base = dev->base_addr;
    unsigned long mem_base = nic_base - HYDRA_NIC_BASE;

    if (count&1)
	count++;

    z_memcpy_toio(mem_base+((start_page - NESM_START_PG)<<8), buf, count);
}