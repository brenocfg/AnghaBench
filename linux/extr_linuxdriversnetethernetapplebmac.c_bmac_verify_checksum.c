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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SROMAddressBits ; 
 unsigned short read_srom (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_and_select_srom (struct net_device*) ; 

__attribute__((used)) static int
bmac_verify_checksum(struct net_device *dev)
{
	unsigned short data, storedCS;

	reset_and_select_srom(dev);
	data = read_srom(dev, 3, SROMAddressBits);
	storedCS = ((data >> 8) & 0x0ff) | ((data << 8) & 0xff00);

	return 0;
}