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
struct pctv452e_state {int /*<<< orphan*/  c; } ;
struct dvb_usb_device {scalar_t__ priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PCTV_CMD_I2C ; 
 int SYNC_BYTE_IN ; 
 int SYNC_BYTE_OUT ; 
 int dvb_usb_generic_rw (struct dvb_usb_device*,int*,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*,int,int,int,int,int,int,int,int*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static int pctv452e_i2c_msg(struct dvb_usb_device *d, u8 addr,
				const u8 *snd_buf, u8 snd_len,
				u8 *rcv_buf, u8 rcv_len)
{
	struct pctv452e_state *state = (struct pctv452e_state *)d->priv;
	u8 *buf;
	u8 id;
	int ret;

	buf = kmalloc(64, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	id = state->c++;

	ret = -EINVAL;
	if (snd_len > 64 - 7 || rcv_len > 64 - 7)
		goto failed;

	buf[0] = SYNC_BYTE_OUT;
	buf[1] = id;
	buf[2] = PCTV_CMD_I2C;
	buf[3] = snd_len + 3;
	buf[4] = addr << 1;
	buf[5] = snd_len;
	buf[6] = rcv_len;

	memcpy(buf + 7, snd_buf, snd_len);

	ret = dvb_usb_generic_rw(d, buf, 7 + snd_len,
				  buf, /* rcv_len */ 64,
				  /* delay_ms */ 0);
	if (ret < 0)
		goto failed;

	/* TT USB protocol error. */
	ret = -EIO;
	if (SYNC_BYTE_IN != buf[0] || id != buf[1])
		goto failed;

	/* I2C device didn't respond as expected. */
	ret = -EREMOTEIO;
	if (buf[5] < snd_len || buf[6] < rcv_len)
		goto failed;

	memcpy(rcv_buf, buf + 7, rcv_len);

	kfree(buf);
	return rcv_len;

failed:
	err("I2C error %d; %02X %02X  %02X %02X %02X -> %*ph",
	     ret, SYNC_BYTE_OUT, id, addr << 1, snd_len, rcv_len,
	     7, buf);

	kfree(buf);
	return ret;
}