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
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 int drm_dp_msg_header_crc4 (int*,int) ; 

__attribute__((used)) static bool drm_dp_decode_sideband_msg_hdr(struct drm_dp_sideband_msg_hdr *hdr,
					   u8 *buf, int buflen, u8 *hdrlen)
{
	u8 crc4;
	u8 len;
	int i;
	u8 idx;
	if (buf[0] == 0)
		return false;
	len = 3;
	len += ((buf[0] & 0xf0) >> 4) / 2;
	if (len > buflen)
		return false;
	crc4 = drm_dp_msg_header_crc4(buf, (len * 2) - 1);

	if ((crc4 & 0xf) != (buf[len - 1] & 0xf)) {
		DRM_DEBUG_KMS("crc4 mismatch 0x%x 0x%x\n", crc4, buf[len - 1]);
		return false;
	}

	hdr->lct = (buf[0] & 0xf0) >> 4;
	hdr->lcr = (buf[0] & 0xf);
	idx = 1;
	for (i = 0; i < (hdr->lct / 2); i++)
		hdr->rad[i] = buf[idx++];
	hdr->broadcast = (buf[idx] >> 7) & 0x1;
	hdr->path_msg = (buf[idx] >> 6) & 0x1;
	hdr->msg_len = buf[idx] & 0x3f;
	idx++;
	hdr->somt = (buf[idx] >> 7) & 0x1;
	hdr->eomt = (buf[idx] >> 6) & 0x1;
	hdr->seqno = (buf[idx] >> 4) & 0x1;
	idx++;
	*hdrlen = idx;
	return true;
}