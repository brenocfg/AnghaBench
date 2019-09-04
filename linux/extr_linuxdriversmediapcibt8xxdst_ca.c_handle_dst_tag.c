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
typedef  int u32 ;
struct dst_state {int dst_hw_cap; } ;
struct ca_msg {int* msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_CA_ERROR ; 
 int DST_TYPE_HAS_SESSION ; 
 int EIO ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int handle_dst_tag(struct dst_state *state, struct ca_msg *p_ca_message, struct ca_msg *hw_buffer, u32 length)
{
	if (state->dst_hw_cap & DST_TYPE_HAS_SESSION) {
		hw_buffer->msg[2] = p_ca_message->msg[1];	/*	MSB	*/
		hw_buffer->msg[3] = p_ca_message->msg[2];	/*	LSB	*/
	} else {
		if (length > 247) {
			dprintk(verbose, DST_CA_ERROR, 1, " Message too long ! *** Bailing Out *** !");
			return -EIO;
		}
		hw_buffer->msg[0] = (length & 0xff) + 7;
		hw_buffer->msg[1] = 0x40;
		hw_buffer->msg[2] = 0x03;
		hw_buffer->msg[3] = 0x00;
		hw_buffer->msg[4] = 0x03;
		hw_buffer->msg[5] = length & 0xff;
		hw_buffer->msg[6] = 0x00;

		/*
		 *	Need to compute length for EN50221 section 8.3.2, for the time being
		 *	assuming 8.3.2 is not applicable
		 */
		memcpy(&hw_buffer->msg[7], &p_ca_message->msg[4], length);
	}

	return 0;
}