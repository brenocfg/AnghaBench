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
typedef  int /*<<< orphan*/  u8 ;
struct dvb_ca_en50221 {struct cxd* data; } ;
struct cxd {int write_busy; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_block (struct cxd*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_reg (struct cxd*,int,int) ; 

__attribute__((used)) static int write_data(struct dvb_ca_en50221 *ca, int slot, u8 *ebuf, int ecount)
{
	struct cxd *ci = ca->data;

	if (ci->write_busy)
		return -EAGAIN;
	mutex_lock(&ci->lock);
	write_reg(ci, 0x0d, ecount >> 8);
	write_reg(ci, 0x0e, ecount & 0xff);
	write_block(ci, 0x11, ebuf, ecount);
	ci->write_busy = 1;
	mutex_unlock(&ci->lock);
	return ecount;
}