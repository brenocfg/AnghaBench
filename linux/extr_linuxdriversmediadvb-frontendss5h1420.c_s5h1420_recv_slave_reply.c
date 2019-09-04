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
struct s5h1420_state {int dummy; } ;
struct dvb_frontend {struct s5h1420_state* demodulator_priv; } ;
struct dvb_diseqc_slave_reply {int timeout; int msg_len; int* msg; } ;

/* Variables and functions */
 int EIO ; 
 int EOVERFLOW ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int s5h1420_readreg (struct s5h1420_state*,int) ; 
 int /*<<< orphan*/  s5h1420_writereg (struct s5h1420_state*,int,int) ; 
 scalar_t__ time_after (int,unsigned long) ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static int s5h1420_recv_slave_reply (struct dvb_frontend* fe,
				     struct dvb_diseqc_slave_reply* reply)
{
	struct s5h1420_state* state = fe->demodulator_priv;
	u8 val;
	int i;
	int length;
	unsigned long timeout;
	int result = 0;

	/* setup for DISEQC receive */
	val = s5h1420_readreg(state, 0x3b);
	s5h1420_writereg(state, 0x3b, 0x82); /* FIXME: guess - do we need to set DIS_RDY(0x08) in receive mode? */
	msleep(15);

	/* wait for reception to complete */
	timeout = jiffies + ((reply->timeout*HZ) / 1000);
	while(time_before(jiffies, timeout)) {
		if (!(s5h1420_readreg(state, 0x3b) & 0x80)) /* FIXME: do we test DIS_RDY(0x08) or RCV_EN(0x80)? */
			break;

		msleep(5);
	}
	if (time_after(jiffies, timeout)) {
		result = -ETIMEDOUT;
		goto exit;
	}

	/* check error flag - FIXME: not sure what this does - docs do not describe
	 * beyond "error flag for diseqc receive data :( */
	if (s5h1420_readreg(state, 0x49)) {
		result = -EIO;
		goto exit;
	}

	/* check length */
	length = (s5h1420_readreg(state, 0x3b) & 0x70) >> 4;
	if (length > sizeof(reply->msg)) {
		result = -EOVERFLOW;
		goto exit;
	}
	reply->msg_len = length;

	/* extract data */
	for(i=0; i< length; i++) {
		reply->msg[i] = s5h1420_readreg(state, 0x3d + i);
	}

exit:
	/* restore original settings */
	s5h1420_writereg(state, 0x3b, val);
	msleep(15);
	return result;
}