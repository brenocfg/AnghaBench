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
struct drm_dp_sideband_msg_hdr {int lct; int lcr; int* rad; int broadcast; int path_msg; int msg_len; int somt; int eomt; int seqno; } ;

/* Variables and functions */
 int drm_dp_msg_header_crc4 (int*,int) ; 

__attribute__((used)) static void drm_dp_encode_sideband_msg_hdr(struct drm_dp_sideband_msg_hdr *hdr,
					   u8 *buf, int *len)
{
	int idx = 0;
	int i;
	u8 crc4;
	buf[idx++] = ((hdr->lct & 0xf) << 4) | (hdr->lcr & 0xf);
	for (i = 0; i < (hdr->lct / 2); i++)
		buf[idx++] = hdr->rad[i];
	buf[idx++] = (hdr->broadcast << 7) | (hdr->path_msg << 6) |
		(hdr->msg_len & 0x3f);
	buf[idx++] = (hdr->somt << 7) | (hdr->eomt << 6) | (hdr->seqno << 4);

	crc4 = drm_dp_msg_header_crc4(buf, (idx * 2) - 1);
	buf[idx - 1] |= (crc4 & 0xf);

	*len = idx;
}