#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct saa7146_dev {TYPE_1__* vv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* irq_done ) (struct saa7146_dev*,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* irq_done ) (struct saa7146_dev*,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  vbi_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_INT (char*,...) ; 
 int MASK_15 ; 
 int MASK_27 ; 
 int MASK_28 ; 
 int /*<<< orphan*/  MASK_31 ; 
 int /*<<< orphan*/  MC2 ; 
 int saa7146_read (struct saa7146_dev*,int /*<<< orphan*/ ) ; 
 TYPE_3__ saa7146_vbi_uops ; 
 TYPE_2__ saa7146_video_uops ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct saa7146_dev*,int) ; 
 int /*<<< orphan*/  stub2 (struct saa7146_dev*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vv_callback(struct saa7146_dev *dev, unsigned long status)
{
	u32 isr = status;

	DEB_INT("dev:%p, isr:0x%08x\n", dev, (u32)status);

	if (0 != (isr & (MASK_27))) {
		DEB_INT("irq: RPS0 (0x%08x)\n", isr);
		saa7146_video_uops.irq_done(dev,isr);
	}

	if (0 != (isr & (MASK_28))) {
		u32 mc2 = saa7146_read(dev, MC2);
		if( 0 != (mc2 & MASK_15)) {
			DEB_INT("irq: RPS1 vbi workaround (0x%08x)\n", isr);
			wake_up(&dev->vv_data->vbi_wq);
			saa7146_write(dev,MC2, MASK_31);
			return;
		}
		DEB_INT("irq: RPS1 (0x%08x)\n", isr);
		saa7146_vbi_uops.irq_done(dev,isr);
	}
}