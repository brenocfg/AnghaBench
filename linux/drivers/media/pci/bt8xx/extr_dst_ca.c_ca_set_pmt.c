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
typedef  int u32 ;
struct dst_state {int dummy; } ;
struct ca_msg {int /*<<< orphan*/ * msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_CA_DEBUG ; 
 int asn_1_decode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_string (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  handle_dst_tag (struct dst_state*,struct ca_msg*,struct ca_msg*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  put_checksum (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose ; 
 int /*<<< orphan*/  write_to_8820 (struct dst_state*,struct ca_msg*,int,int) ; 

__attribute__((used)) static int ca_set_pmt(struct dst_state *state, struct ca_msg *p_ca_message, struct ca_msg *hw_buffer, u8 reply, u8 query)
{
	u32 length = 0;
	u8 tag_length = 8;

	length = asn_1_decode(&p_ca_message->msg[3]);
	dprintk(verbose, DST_CA_DEBUG, 1, " CA Message length=[%d]", length);
	debug_string(&p_ca_message->msg[4], length, 0); /*	length is excluding tag & length	*/

	memset(hw_buffer->msg, '\0', length);
	handle_dst_tag(state, p_ca_message, hw_buffer, length);
	put_checksum(hw_buffer->msg, hw_buffer->msg[0]);

	debug_string(hw_buffer->msg, (length + tag_length), 0); /*	tags too	*/
	write_to_8820(state, hw_buffer, (length + tag_length), reply);

	return 0;
}