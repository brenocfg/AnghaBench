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
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_5__ {int /*<<< orphan*/  highvals; int /*<<< orphan*/  mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  enable; int /*<<< orphan*/  mask; } ;
union dst_gpio_packet {int /*<<< orphan*/  psize; TYPE_3__ rd; TYPE_2__ outp; TYPE_1__ enb; } ;
struct bt878 {int /*<<< orphan*/  gpio_lock; int /*<<< orphan*/  TS_Size; int /*<<< orphan*/  bttv_nr; } ;

/* Variables and functions */
#define  DST_IG_ENABLE 131 
#define  DST_IG_READ 130 
#define  DST_IG_TS 129 
#define  DST_IG_WRITE 128 
 int EINVAL ; 
 int ERESTARTSYS ; 
 int bttv_gpio_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bttv_read_gpio (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bttv_write_gpio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int
bt878_device_control(struct bt878 *bt, unsigned int cmd, union dst_gpio_packet *mp)
{
	int retval;

	retval = 0;
	if (mutex_lock_interruptible(&bt->gpio_lock))
		return -ERESTARTSYS;
	/* special gpio signal */
	switch (cmd) {
	    case DST_IG_ENABLE:
		// dprintk("dvb_bt8xx: dst enable mask 0x%02x enb 0x%02x \n", mp->dstg.enb.mask, mp->dstg.enb.enable);
		retval = bttv_gpio_enable(bt->bttv_nr,
				mp->enb.mask,
				mp->enb.enable);
		break;
	    case DST_IG_WRITE:
		// dprintk("dvb_bt8xx: dst write gpio mask 0x%02x out 0x%02x\n", mp->dstg.outp.mask, mp->dstg.outp.highvals);
		retval = bttv_write_gpio(bt->bttv_nr,
				mp->outp.mask,
				mp->outp.highvals);

		break;
	    case DST_IG_READ:
		/* read */
		retval =  bttv_read_gpio(bt->bttv_nr, &mp->rd.value);
		// dprintk("dvb_bt8xx: dst read gpio 0x%02x\n", (unsigned)mp->dstg.rd.value);
		break;
	    case DST_IG_TS:
		/* Set packet size */
		bt->TS_Size = mp->psize;
		break;

	    default:
		retval = -EINVAL;
		break;
	}
	mutex_unlock(&bt->gpio_lock);
	return retval;
}