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
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__* grab_buffer; int /*<<< orphan*/  grab_fbuffer; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ MEYE_BUF_DONE ; 
 scalar_t__ MEYE_BUF_UNUSED ; 
 scalar_t__ MEYE_BUF_USING ; 
 int /*<<< orphan*/  mchip_get_picture (int /*<<< orphan*/ ,int) ; 
 int mchip_hsize () ; 
 int /*<<< orphan*/  mchip_take_picture () ; 
 int mchip_vsize () ; 
 TYPE_2__ meye ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int meyeioc_stillcapt(void)
{
	if (!meye.grab_fbuffer)
		return -EINVAL;

	if (meye.grab_buffer[0].state != MEYE_BUF_UNUSED)
		return -EBUSY;

	mutex_lock(&meye.lock);
	meye.grab_buffer[0].state = MEYE_BUF_USING;
	mchip_take_picture();

	mchip_get_picture(meye.grab_fbuffer,
			mchip_hsize() * mchip_vsize() * 2);

	meye.grab_buffer[0].state = MEYE_BUF_DONE;
	mutex_unlock(&meye.lock);

	return 0;
}