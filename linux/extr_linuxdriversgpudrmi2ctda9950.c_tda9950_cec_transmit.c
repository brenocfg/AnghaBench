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
typedef  int /*<<< orphan*/  u32 ;
struct tda9950_priv {int /*<<< orphan*/  client; } ;
struct cec_msg {int len; int /*<<< orphan*/  msg; } ;
struct cec_adapter {struct tda9950_priv* priv; } ;

/* Variables and functions */
 int CDR1_REQ ; 
 int /*<<< orphan*/  CEC_MAX_MSG_SIZE ; 
 int /*<<< orphan*/  REG_CCONR ; 
 int /*<<< orphan*/  REG_CDR0 ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tda9950_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int tda9950_write_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int tda9950_cec_transmit(struct cec_adapter *adap, u8 attempts,
				u32 signal_free_time, struct cec_msg *msg)
{
	struct tda9950_priv *priv = adap->priv;
	u8 buf[CEC_MAX_MSG_SIZE + 2];

	buf[0] = 2 + msg->len;
	buf[1] = CDR1_REQ;
	memcpy(buf + 2, msg->msg, msg->len);

	if (attempts > 5)
		attempts = 5;

	tda9950_write(priv->client, REG_CCONR, attempts);

	return tda9950_write_range(priv->client, REG_CDR0, buf, 2 + msg->len);
}