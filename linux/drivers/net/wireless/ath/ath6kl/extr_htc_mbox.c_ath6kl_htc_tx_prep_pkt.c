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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct htc_packet {int /*<<< orphan*/  endpoint; scalar_t__ act_len; scalar_t__ buf; } ;
struct htc_frame_hdr {int* ctrl; int /*<<< orphan*/  eid; int /*<<< orphan*/  flags; int /*<<< orphan*/  payld_len; } ;

/* Variables and functions */
 scalar_t__ HTC_HDR_LENGTH ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath6kl_htc_tx_prep_pkt(struct htc_packet *packet, u8 flags,
				   int ctrl0, int ctrl1)
{
	struct htc_frame_hdr *hdr;

	packet->buf -= HTC_HDR_LENGTH;
	hdr =  (struct htc_frame_hdr *)packet->buf;

	/* Endianess? */
	put_unaligned((u16)packet->act_len, &hdr->payld_len);
	hdr->flags = flags;
	hdr->eid = packet->endpoint;
	hdr->ctrl[0] = ctrl0;
	hdr->ctrl[1] = ctrl1;
}