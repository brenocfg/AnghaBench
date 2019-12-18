#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct tty_struct {int dummy; } ;
struct TYPE_5__ {struct tty_struct* tty; } ;
struct TYPE_6__ {int data_rate; int loopback; int /*<<< orphan*/  mode; } ;
struct slgt_info {int tmp_rbuf_count; int /*<<< orphan*/  init_error; TYPE_1__ port; TYPE_2__ params; int /*<<< orphan*/  lock; int /*<<< orphan*/  tmp_rbuf; } ;
typedef  int /*<<< orphan*/  params ;
typedef  TYPE_2__ MGSL_PARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  DiagStatus_DmaFailure ; 
 int ENODEV ; 
 int /*<<< orphan*/  MGSL_MODE_ASYNC ; 
 int TESTFRAMESIZE ; 
 int /*<<< orphan*/  async_mode (struct slgt_info*) ; 
 scalar_t__ loopback_test_rx (struct slgt_info*) ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  reset_adapter (struct slgt_info*) ; 
 int /*<<< orphan*/  rx_start (struct slgt_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_load (struct slgt_info*,unsigned char*,int) ; 

__attribute__((used)) static int loopback_test(struct slgt_info *info)
{
#define TESTFRAMESIZE 20

	unsigned long timeout;
	u16 count = TESTFRAMESIZE;
	unsigned char buf[TESTFRAMESIZE];
	int rc = -ENODEV;
	unsigned long flags;

	struct tty_struct *oldtty = info->port.tty;
	MGSL_PARAMS params;

	memcpy(&params, &info->params, sizeof(params));

	info->params.mode = MGSL_MODE_ASYNC;
	info->params.data_rate = 921600;
	info->params.loopback = 1;
	info->port.tty = NULL;

	/* build and send transmit frame */
	for (count = 0; count < TESTFRAMESIZE; ++count)
		buf[count] = (unsigned char)count;

	info->tmp_rbuf_count = 0;
	memset(info->tmp_rbuf, 0, TESTFRAMESIZE);

	/* program hardware for HDLC and enabled receiver */
	spin_lock_irqsave(&info->lock,flags);
	async_mode(info);
	rx_start(info);
	tx_load(info, buf, count);
	spin_unlock_irqrestore(&info->lock, flags);

	/* wait for receive complete */
	for (timeout = 100; timeout; --timeout) {
		msleep_interruptible(10);
		if (loopback_test_rx(info)) {
			rc = 0;
			break;
		}
	}

	/* verify received frame length and contents */
	if (!rc && (info->tmp_rbuf_count != count ||
		  memcmp(buf, info->tmp_rbuf, count))) {
		rc = -ENODEV;
	}

	spin_lock_irqsave(&info->lock,flags);
	reset_adapter(info);
	spin_unlock_irqrestore(&info->lock,flags);

	memcpy(&info->params, &params, sizeof(info->params));
	info->port.tty = oldtty;

	info->init_error = rc ? DiagStatus_DmaFailure : 0;
	return rc;
}