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
struct fmi {int /*<<< orphan*/  lock; int /*<<< orphan*/  io; scalar_t__ mute; } ;

/* Variables and functions */
 scalar_t__ inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int fmi_getsigstr(struct fmi *fmi)
{
	int val;
	int res;

	mutex_lock(&fmi->lock);
	val = fmi->mute ? 0x00 : 0x08;	/* mute/unmute */
	outb(val, fmi->io);
	outb(val | 0x10, fmi->io);
	msleep(143);		/* was schedule_timeout(HZ/7) */
	res = (int)inb(fmi->io + 1);
	outb(val, fmi->io);

	mutex_unlock(&fmi->lock);
	return (res & 2) ? 0 : 0xFFFF;
}