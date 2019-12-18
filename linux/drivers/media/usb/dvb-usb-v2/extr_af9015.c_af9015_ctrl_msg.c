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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct req_t {int cmd; int i2c_addr; int addr; int mbox; int addr_len; int data_len; int* data; } ;
struct dvb_usb_device {int /*<<< orphan*/  usb_mutex; struct usb_interface* intf; } ;
struct af9015_state {int* buf; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 size_t ACK_HDR_LEN ; 
#define  BOOT 137 
 int BUF_LEN ; 
#define  COPY_FIRMWARE 136 
#define  DOWNLOAD_FIRMWARE 135 
 int EINVAL ; 
 int EIO ; 
#define  GET_CONFIG 134 
#define  READ_I2C 133 
#define  READ_MEMORY 132 
 int READ_WRITE_I2C ; 
#define  RECONNECT_USB 131 
 size_t REQ_HDR_LEN ; 
#define  WRITE_I2C 130 
#define  WRITE_MEMORY 129 
#define  WRITE_VIRTUAL_MEMORY 128 
 struct af9015_state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int dvb_usbv2_generic_rw_locked (struct dvb_usb_device*,int*,int,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int af9015_ctrl_msg(struct dvb_usb_device *d, struct req_t *req)
{
#define REQ_HDR_LEN 8 /* send header size */
#define ACK_HDR_LEN 2 /* rece header size */
	struct af9015_state *state = d_to_priv(d);
	struct usb_interface *intf = d->intf;
	int ret, wlen, rlen;
	u8 write = 1;

	mutex_lock(&d->usb_mutex);

	state->buf[0] = req->cmd;
	state->buf[1] = state->seq++;
	state->buf[2] = req->i2c_addr << 1;
	state->buf[3] = req->addr >> 8;
	state->buf[4] = req->addr & 0xff;
	state->buf[5] = req->mbox;
	state->buf[6] = req->addr_len;
	state->buf[7] = req->data_len;

	switch (req->cmd) {
	case GET_CONFIG:
	case READ_MEMORY:
	case RECONNECT_USB:
		write = 0;
		break;
	case READ_I2C:
		write = 0;
		state->buf[2] |= 0x01; /* set I2C direction */
		/* fall through */
	case WRITE_I2C:
		state->buf[0] = READ_WRITE_I2C;
		break;
	case WRITE_MEMORY:
		if (((req->addr & 0xff00) == 0xff00) ||
		    ((req->addr & 0xff00) == 0xae00))
			state->buf[0] = WRITE_VIRTUAL_MEMORY;
	case WRITE_VIRTUAL_MEMORY:
	case COPY_FIRMWARE:
	case DOWNLOAD_FIRMWARE:
	case BOOT:
		break;
	default:
		dev_err(&intf->dev, "unknown cmd %d\n", req->cmd);
		ret = -EIO;
		goto error;
	}

	/* Buffer overflow check */
	if ((write && (req->data_len > BUF_LEN - REQ_HDR_LEN)) ||
	    (!write && (req->data_len > BUF_LEN - ACK_HDR_LEN))) {
		dev_err(&intf->dev, "too much data, cmd %u, len %u\n",
			req->cmd, req->data_len);
		ret = -EINVAL;
		goto error;
	}

	/*
	 * Write receives seq + status = 2 bytes
	 * Read receives seq + status + data = 2 + N bytes
	 */
	wlen = REQ_HDR_LEN;
	rlen = ACK_HDR_LEN;
	if (write) {
		wlen += req->data_len;
		memcpy(&state->buf[REQ_HDR_LEN], req->data, req->data_len);
	} else {
		rlen += req->data_len;
	}

	/* no ack for these packets */
	if (req->cmd == DOWNLOAD_FIRMWARE || req->cmd == RECONNECT_USB)
		rlen = 0;

	ret = dvb_usbv2_generic_rw_locked(d, state->buf, wlen,
					  state->buf, rlen);
	if (ret)
		goto error;

	/* check status */
	if (rlen && state->buf[1]) {
		dev_err(&intf->dev, "cmd failed %u\n", state->buf[1]);
		ret = -EIO;
		goto error;
	}

	/* read request, copy returned data to return buf */
	if (!write)
		memcpy(req->data, &state->buf[ACK_HDR_LEN], req->data_len);
error:
	mutex_unlock(&d->usb_mutex);

	return ret;
}