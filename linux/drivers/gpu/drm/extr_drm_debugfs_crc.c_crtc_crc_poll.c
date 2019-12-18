#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file {TYPE_1__* f_inode; } ;
struct drm_crtc_crc {int /*<<< orphan*/  lock; scalar_t__ source; int /*<<< orphan*/  wq; } ;
struct drm_crtc {struct drm_crtc_crc crc; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_2__ {struct drm_crtc* i_private; } ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 scalar_t__ crtc_crc_data_count (struct drm_crtc_crc*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int crtc_crc_poll(struct file *file, poll_table *wait)
{
	struct drm_crtc *crtc = file->f_inode->i_private;
	struct drm_crtc_crc *crc = &crtc->crc;
	unsigned ret;

	poll_wait(file, &crc->wq, wait);

	spin_lock_irq(&crc->lock);
	if (crc->source && crtc_crc_data_count(crc))
		ret = POLLIN | POLLRDNORM;
	else
		ret = 0;
	spin_unlock_irq(&crc->lock);

	return ret;
}