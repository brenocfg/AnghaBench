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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int is_present; int word; } ;
struct TYPE_3__ {int byte; } ;
struct hip_hdr {scalar_t__ hdrlen; TYPE_2__ payload_len; TYPE_2__ extmsgid; TYPE_1__ msgid; TYPE_1__ msgspecific; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTO ; 
 int SIERRA_NET_HIP_EXTENDEDID ; 
 scalar_t__ const SIERRA_NET_HIP_EXT_HDR_LEN ; 
 scalar_t__ const SIERRA_NET_HIP_HDR_LEN ; 
 int /*<<< orphan*/ * save16bit (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * save8bit (TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int parse_hip(const u8 *buf, const u32 buflen, struct hip_hdr *hh)
{
	const u8 *curp = buf;
	int    padded;

	if (buflen < SIERRA_NET_HIP_HDR_LEN)
		return -EPROTO;

	curp = save16bit(&hh->payload_len, curp);
	curp = save8bit(&hh->msgid, curp);
	curp = save8bit(&hh->msgspecific, curp);

	padded = hh->msgid.byte & 0x80;
	hh->msgid.byte &= 0x7F;			/* 7 bits */

	hh->extmsgid.is_present = (hh->msgid.byte == SIERRA_NET_HIP_EXTENDEDID);
	if (hh->extmsgid.is_present) {
		if (buflen < SIERRA_NET_HIP_EXT_HDR_LEN)
			return -EPROTO;

		hh->payload_len.word &= 0x3FFF; /* 14 bits */

		curp = save16bit(&hh->extmsgid, curp);
		hh->extmsgid.word &= 0x03FF;	/* 10 bits */

		hh->hdrlen = SIERRA_NET_HIP_EXT_HDR_LEN;
	} else {
		hh->payload_len.word &= 0x07FF;	/* 11 bits */
		hh->hdrlen = SIERRA_NET_HIP_HDR_LEN;
	}

	if (padded) {
		hh->hdrlen++;
		hh->payload_len.word--;
	}

	/* if real packet shorter than the claimed length */
	if (buflen < (hh->hdrlen + hh->payload_len.word))
		return -EINVAL;

	return 0;
}