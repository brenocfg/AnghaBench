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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct gma_encoder {int dummy; } ;

/* Variables and functions */
 int DP_AUX_NATIVE_READ ; 
 int DP_AUX_NATIVE_REPLY_ACK ; 
 int DP_AUX_NATIVE_REPLY_DEFER ; 
 int DP_AUX_NATIVE_REPLY_MASK ; 
 int EIO ; 
 int EPROTO ; 
 int cdv_intel_dp_aux_ch (struct gma_encoder*,int*,int,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
cdv_intel_dp_aux_native_read(struct gma_encoder *encoder,
			 uint16_t address, uint8_t *recv, int recv_bytes)
{
	uint8_t msg[4];
	int msg_bytes;
	uint8_t reply[20];
	int reply_bytes;
	uint8_t ack;
	int ret;

	msg[0] = DP_AUX_NATIVE_READ << 4;
	msg[1] = address >> 8;
	msg[2] = address & 0xff;
	msg[3] = recv_bytes - 1;

	msg_bytes = 4;
	reply_bytes = recv_bytes + 1;

	for (;;) {
		ret = cdv_intel_dp_aux_ch(encoder, msg, msg_bytes,
				      reply, reply_bytes);
		if (ret == 0)
			return -EPROTO;
		if (ret < 0)
			return ret;
		ack = reply[0] >> 4;
		if ((ack & DP_AUX_NATIVE_REPLY_MASK) == DP_AUX_NATIVE_REPLY_ACK) {
			memcpy(recv, reply + 1, ret - 1);
			return ret - 1;
		}
		else if ((ack & DP_AUX_NATIVE_REPLY_MASK) == DP_AUX_NATIVE_REPLY_DEFER)
			udelay(100);
		else
			return -EIO;
	}
}