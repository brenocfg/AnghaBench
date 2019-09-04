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
typedef  int /*<<< orphan*/  u_char ;
struct net_device {unsigned int base_addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ AXNET_CMD ; 
 scalar_t__ AXNET_DATAPORT ; 
 int const E8390_RWRITE ; 
 int const E8390_START ; 
 scalar_t__ EN0_RSARHI ; 
 scalar_t__ EN0_RSARLO ; 
 int /*<<< orphan*/  outb_p (int const,scalar_t__) ; 
 int /*<<< orphan*/  outsw (scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void block_output(struct net_device *dev, int count,
			 const u_char *buf, const int start_page)
{
    unsigned int nic_base = dev->base_addr;

    pr_debug("%s: [bo=%d]\n", dev->name, count);

    /* Round the count up for word writes.  Do we need to do this?
       What effect will an odd byte count have on the 8390?
       I should check someday. */
    if (count & 0x01)
	count++;

    outb_p(0x00, nic_base + EN0_RSARLO);
    outb_p(start_page, nic_base + EN0_RSARHI);
    outb_p(E8390_RWRITE+E8390_START, nic_base + AXNET_CMD);
    outsw(nic_base + AXNET_DATAPORT, buf, count>>1);
}