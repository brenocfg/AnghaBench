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
typedef  int u16 ;
struct rtllib_hdr_4addr {int* addr4; int* addr2; int* addr1; int /*<<< orphan*/  seq_ctl; int /*<<< orphan*/  frame_ctl; } ;

/* Variables and functions */
 int CCMP_PN_LEN ; 
 int ETH_ALEN ; 
 int RTLLIB_FCTL_FROMDS ; 
 int RTLLIB_FCTL_TODS ; 
 scalar_t__ RTLLIB_FTYPE_DATA ; 
 int WLAN_FC_GET_STYPE (int) ; 
 scalar_t__ WLAN_FC_GET_TYPE (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ccmp_init_iv_and_aad(struct rtllib_hdr_4addr *hdr,
				u8 *pn, u8 *iv, u8 *aad)
{
	u8 *pos, qc = 0;
	size_t aad_len;
	u16 fc;
	int a4_included, qc_included;

	fc = le16_to_cpu(hdr->frame_ctl);
	a4_included = ((fc & (RTLLIB_FCTL_TODS | RTLLIB_FCTL_FROMDS)) ==
		       (RTLLIB_FCTL_TODS | RTLLIB_FCTL_FROMDS));

	qc_included = ((WLAN_FC_GET_TYPE(fc) == RTLLIB_FTYPE_DATA) &&
		       (WLAN_FC_GET_STYPE(fc) & 0x80));
	aad_len = 22;
	if (a4_included)
		aad_len += 6;
	if (qc_included) {
		pos = (u8 *) &hdr->addr4;
		if (a4_included)
			pos += 6;
		qc = *pos & 0x0f;
		aad_len += 2;
	}
	/* In CCM, the initial vectors (IV) used for CTR mode encryption and CBC
	 * mode authentication are not allowed to collide, yet both are derived
	 * from the same vector. We only set L := 1 here to indicate that the
	 * data size can be represented in (L+1) bytes. The CCM layer will take
	 * care of storing the data length in the top (L+1) bytes and setting
	 * and clearing the other bits as is required to derive the two IVs.
	 */
	iv[0] = 0x1;

	/* Nonce: QC | A2 | PN */
	iv[1] = qc;
	memcpy(iv + 2, hdr->addr2, ETH_ALEN);
	memcpy(iv + 8, pn, CCMP_PN_LEN);

	/* AAD:
	 * FC with bits 4..6 and 11..13 masked to zero; 14 is always one
	 * A1 | A2 | A3
	 * SC with bits 4..15 (seq#) masked to zero
	 * A4 (if present)
	 * QC (if present)
	 */
	pos = (u8 *) hdr;
	aad[0] = pos[0] & 0x8f;
	aad[1] = pos[1] & 0xc7;
	memcpy(aad + 2, hdr->addr1, 3 * ETH_ALEN);
	pos = (u8 *) &hdr->seq_ctl;
	aad[20] = pos[0] & 0x0f;
	aad[21] = 0; /* all bits masked */
	memset(aad + 22, 0, 8);
	if (a4_included)
		memcpy(aad + 22, hdr->addr4, ETH_ALEN);
	if (qc_included) {
		aad[a4_included ? 28 : 22] = qc;
		/* rest of QC masked */
	}

	return aad_len;
}