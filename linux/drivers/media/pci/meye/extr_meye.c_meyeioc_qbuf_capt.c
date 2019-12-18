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
struct TYPE_4__ {scalar_t__ mchip_mode; int /*<<< orphan*/  lock; int /*<<< orphan*/  grabq_lock; int /*<<< orphan*/  grabq; TYPE_1__* grab_buffer; int /*<<< orphan*/  grab_fbuffer; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ MCHIP_HIC_MODE_CONT_COMP ; 
 scalar_t__ MEYE_BUF_UNUSED ; 
 scalar_t__ MEYE_BUF_USING ; 
 int gbuffers ; 
 int /*<<< orphan*/  kfifo_in_locked (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mchip_cont_compression_start () ; 
 int /*<<< orphan*/  mchip_hic_stop () ; 
 TYPE_2__ meye ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int meyeioc_qbuf_capt(int *nb)
{
	if (!meye.grab_fbuffer)
		return -EINVAL;

	if (*nb >= gbuffers)
		return -EINVAL;

	if (*nb < 0) {
		/* stop capture */
		mchip_hic_stop();
		return 0;
	}

	if (meye.grab_buffer[*nb].state != MEYE_BUF_UNUSED)
		return -EBUSY;

	mutex_lock(&meye.lock);

	if (meye.mchip_mode != MCHIP_HIC_MODE_CONT_COMP)
		mchip_cont_compression_start();

	meye.grab_buffer[*nb].state = MEYE_BUF_USING;
	kfifo_in_locked(&meye.grabq, (unsigned char *)nb, sizeof(int),
			 &meye.grabq_lock);
	mutex_unlock(&meye.lock);

	return 0;
}