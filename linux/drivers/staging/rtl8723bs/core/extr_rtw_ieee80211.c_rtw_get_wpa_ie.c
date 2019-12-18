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
typedef  int /*<<< orphan*/  wpa_oui_type ;
typedef  int /*<<< orphan*/  val16 ;
typedef  unsigned char u8 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  _WPA_IE_ID_ ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 unsigned char* rtw_get_ie (unsigned char*,int /*<<< orphan*/ ,int*,int) ; 

unsigned char *rtw_get_wpa_ie(unsigned char *pie, int *wpa_ie_len, int limit)
{
	int len;
	u16 val16;
	unsigned char wpa_oui_type[] = {0x00, 0x50, 0xf2, 0x01};
	u8 *pbuf = pie;
	int limit_new = limit;
	__le16 le_tmp;

	while (1) {
		pbuf = rtw_get_ie(pbuf, _WPA_IE_ID_, &len, limit_new);

		if (pbuf) {
			/* check if oui matches... */
			if (memcmp((pbuf + 2), wpa_oui_type, sizeof(wpa_oui_type))) {
				goto check_next_ie;
			}

			/* check version... */
			memcpy((u8 *)&le_tmp, (pbuf + 6), sizeof(val16));

			val16 = le16_to_cpu(le_tmp);
			if (val16 != 0x0001)
				goto check_next_ie;

			*wpa_ie_len = *(pbuf + 1);

			return pbuf;

		} else {
			*wpa_ie_len = 0;
			return NULL;
		}

check_next_ie:

		limit_new = limit - (pbuf - pie) - 2 - len;

		if (limit_new <= 0)
			break;

		pbuf += (2 + len);
	}

	*wpa_ie_len = 0;

	return NULL;
}