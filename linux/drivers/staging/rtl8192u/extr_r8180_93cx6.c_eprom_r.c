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
typedef  int u8 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROM_CMD ; 
 int /*<<< orphan*/  EPROM_DELAY ; 
 int EPROM_R_BIT ; 
 int read_nic_byte_E (struct net_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static short eprom_r(struct net_device *dev)
{
	u8 bit;
	int err;

	err = read_nic_byte_E(dev, EPROM_CMD, &bit);
	if (err)
		return err;

	udelay(EPROM_DELAY);

	if (bit & EPROM_R_BIT)
		return 1;

	return 0;
}