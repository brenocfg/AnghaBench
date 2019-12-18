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
 int /*<<< orphan*/  SSB_TPSFLAG ; 
 int SSB_TPSFLAG_BPFLAG ; 
 int ssb_read32 (struct ssb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 ssb_irqflag(struct ssb_device *dev)
{
	u32 tpsflag = ssb_read32(dev, SSB_TPSFLAG);
	if (tpsflag)
		return ssb_read32(dev, SSB_TPSFLAG) & SSB_TPSFLAG_BPFLAG;
	else
		/* not irq supported */
		return 0x3f;
}