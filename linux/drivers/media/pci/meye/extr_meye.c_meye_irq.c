#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {scalar_t__ mchip_mode; int /*<<< orphan*/  proc_list; int /*<<< orphan*/  doneq_lock; int /*<<< orphan*/  doneq; TYPE_1__* grab_buffer; int /*<<< orphan*/  grab_temp; scalar_t__ grab_fbuffer; int /*<<< orphan*/  grabq_lock; int /*<<< orphan*/  grabq; } ;
struct TYPE_3__ {int size; int /*<<< orphan*/  sequence; void* ts; void* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ MCHIP_HIC_MODE_CONT_COMP ; 
 scalar_t__ MCHIP_HIC_MODE_CONT_OUT ; 
 int MCHIP_MM_FIR_RDY ; 
 int /*<<< orphan*/  MCHIP_MM_INTA ; 
 void* MEYE_BUF_DONE ; 
 int gbufsize ; 
 int /*<<< orphan*/  kfifo_in_locked (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ *) ; 
 int kfifo_out_locked (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ *) ; 
 void* ktime_get_ns () ; 
 int mchip_comp_read_frame (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mchip_cont_read_frame (int,scalar_t__,int) ; 
 int /*<<< orphan*/  mchip_free_frame () ; 
 int mchip_get_frame () ; 
 int mchip_hsize () ; 
 int mchip_read (int /*<<< orphan*/ ) ; 
 int mchip_vsize () ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ meye ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t meye_irq(int irq, void *dev_id)
{
	u32 v;
	int reqnr;
	static int sequence;

	v = mchip_read(MCHIP_MM_INTA);

	if (meye.mchip_mode != MCHIP_HIC_MODE_CONT_OUT &&
	    meye.mchip_mode != MCHIP_HIC_MODE_CONT_COMP)
		return IRQ_NONE;

again:
	v = mchip_get_frame();
	if (!(v & MCHIP_MM_FIR_RDY))
		return IRQ_HANDLED;

	if (meye.mchip_mode == MCHIP_HIC_MODE_CONT_OUT) {
		if (kfifo_out_locked(&meye.grabq, (unsigned char *)&reqnr,
			      sizeof(int), &meye.grabq_lock) != sizeof(int)) {
			mchip_free_frame();
			return IRQ_HANDLED;
		}
		mchip_cont_read_frame(v, meye.grab_fbuffer + gbufsize * reqnr,
				      mchip_hsize() * mchip_vsize() * 2);
		meye.grab_buffer[reqnr].size = mchip_hsize() * mchip_vsize() * 2;
		meye.grab_buffer[reqnr].state = MEYE_BUF_DONE;
		meye.grab_buffer[reqnr].ts = ktime_get_ns();
		meye.grab_buffer[reqnr].sequence = sequence++;
		kfifo_in_locked(&meye.doneq, (unsigned char *)&reqnr,
				sizeof(int), &meye.doneq_lock);
		wake_up_interruptible(&meye.proc_list);
	} else {
		int size;
		size = mchip_comp_read_frame(v, meye.grab_temp, gbufsize);
		if (size == -1) {
			mchip_free_frame();
			goto again;
		}
		if (kfifo_out_locked(&meye.grabq, (unsigned char *)&reqnr,
			      sizeof(int), &meye.grabq_lock) != sizeof(int)) {
			mchip_free_frame();
			goto again;
		}
		memcpy(meye.grab_fbuffer + gbufsize * reqnr, meye.grab_temp,
		       size);
		meye.grab_buffer[reqnr].size = size;
		meye.grab_buffer[reqnr].state = MEYE_BUF_DONE;
		meye.grab_buffer[reqnr].ts = ktime_get_ns();
		meye.grab_buffer[reqnr].sequence = sequence++;
		kfifo_in_locked(&meye.doneq, (unsigned char *)&reqnr,
				sizeof(int), &meye.doneq_lock);
		wake_up_interruptible(&meye.proc_list);
	}
	mchip_free_frame();
	goto again;
}