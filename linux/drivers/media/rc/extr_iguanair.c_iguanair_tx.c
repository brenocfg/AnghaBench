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
struct rc_dev {struct iguanair* priv; } ;
struct iguanair {unsigned int carrier; unsigned int bufsize; int tx_overflow; int /*<<< orphan*/  lock; TYPE_2__* packet; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  direction; scalar_t__ start; } ;
struct TYPE_4__ {unsigned int* payload; unsigned int length; TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SEND ; 
 int /*<<< orphan*/  DIR_OUT ; 
 unsigned int DIV_ROUND_CLOSEST (unsigned int,int) ; 
 int EINVAL ; 
 int EOVERFLOW ; 
 int iguanair_send (struct iguanair*,int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iguanair_tx(struct rc_dev *dev, unsigned *txbuf, unsigned count)
{
	struct iguanair *ir = dev->priv;
	unsigned int i, size, p, periods;
	int rc;

	mutex_lock(&ir->lock);

	/* convert from us to carrier periods */
	for (i = size = 0; i < count; i++) {
		periods = DIV_ROUND_CLOSEST(txbuf[i] * ir->carrier, 1000000);
		while (periods) {
			p = min(periods, 127u);
			if (size >= ir->bufsize) {
				rc = -EINVAL;
				goto out;
			}
			ir->packet->payload[size++] = p | ((i & 1) ? 0x80 : 0);
			periods -= p;
		}
	}

	ir->packet->header.start = 0;
	ir->packet->header.direction = DIR_OUT;
	ir->packet->header.cmd = CMD_SEND;
	ir->packet->length = size;

	ir->tx_overflow = false;

	rc = iguanair_send(ir, sizeof(*ir->packet) + size);

	if (rc == 0 && ir->tx_overflow)
		rc = -EOVERFLOW;

out:
	mutex_unlock(&ir->lock);

	return rc ? rc : count;
}