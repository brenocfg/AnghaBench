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
typedef  int u16 ;
struct dvb_ca_en50221 {struct cxd* data; } ;
struct cxd {int* rbuf; int /*<<< orphan*/  lock; scalar_t__ dr; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  campoll (struct cxd*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_block (struct cxd*,int,int*,int) ; 
 int /*<<< orphan*/  read_reg (struct cxd*,int,int*) ; 

__attribute__((used)) static int read_data(struct dvb_ca_en50221 *ca, int slot, u8 *ebuf, int ecount)
{
	struct cxd *ci = ca->data;
	u8 msb, lsb;
	u16 len;

	mutex_lock(&ci->lock);
	campoll(ci);
	mutex_unlock(&ci->lock);

	if (!ci->dr)
		return 0;

	mutex_lock(&ci->lock);
	read_reg(ci, 0x0f, &msb);
	read_reg(ci, 0x10, &lsb);
	len = ((u16)msb << 8) | lsb;
	if (len > ecount || len < 2) {
		/* read it anyway or cxd may hang */
		read_block(ci, 0x12, ci->rbuf, len);
		mutex_unlock(&ci->lock);
		return -EIO;
	}
	read_block(ci, 0x12, ebuf, len);
	ci->dr = 0;
	mutex_unlock(&ci->lock);
	return len;
}