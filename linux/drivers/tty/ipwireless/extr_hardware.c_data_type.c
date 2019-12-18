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
struct nl_packet_header {int packet_rank; int protocol; } ;

/* Variables and functions */
 int NL_FIRST_PACKET ; 
#define  TL_PROTOCOLID_COM_CTRL 130 
#define  TL_PROTOCOLID_COM_DATA 129 
#define  TL_PROTOCOLID_SETUP 128 

__attribute__((used)) static char *data_type(const unsigned char *buf, unsigned length)
{
	struct nl_packet_header *hdr = (struct nl_packet_header *) buf;

	if (length == 0)
		return "     ";

	if (hdr->packet_rank & NL_FIRST_PACKET) {
		switch (hdr->protocol) {
		case TL_PROTOCOLID_COM_DATA:	return "DATA ";
		case TL_PROTOCOLID_COM_CTRL:	return "CTRL ";
		case TL_PROTOCOLID_SETUP:	return "SETUP";
		default: return "???? ";
		}
	} else
		return "     ";
}