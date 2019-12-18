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
typedef  int u32 ;
struct ssb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_TMSLOW ; 
 int SSB_TMSLOW_CLOCK ; 
 int SSB_TMSLOW_RESET ; 
 int ssb_read32 (struct ssb_device*,int /*<<< orphan*/ ) ; 
 int ssb_tmslow_reject_bitmask (struct ssb_device*) ; 

int ssb_device_is_enabled(struct ssb_device *dev)
{
	u32 val;
	u32 reject;

	reject = ssb_tmslow_reject_bitmask(dev);
	val = ssb_read32(dev, SSB_TMSLOW);
	val &= SSB_TMSLOW_CLOCK | SSB_TMSLOW_RESET | reject;

	return (val == SSB_TMSLOW_CLOCK);
}