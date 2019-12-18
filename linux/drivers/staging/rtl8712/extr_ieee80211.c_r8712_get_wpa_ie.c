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
typedef  unsigned char uint ;
typedef  unsigned char u8 ;
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  _WPA_IE_ID_ ; 
 int /*<<< orphan*/  le16_to_cpus (int*) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 unsigned char* r8712_get_ie (unsigned char*,int /*<<< orphan*/ ,int*,int) ; 

unsigned char *r8712_get_wpa_ie(unsigned char *ie, uint *wpa_ie_len, int limit)
{
	u32 len;
	u16 val16;
	unsigned char wpa_oui_type[] = {0x00, 0x50, 0xf2, 0x01};
	u8 *buf = ie;

	while (1) {
		buf = r8712_get_ie(buf, _WPA_IE_ID_, &len, limit);
		if (buf) {
			/*check if oui matches...*/
			if (memcmp((buf + 2), wpa_oui_type,
				   sizeof(wpa_oui_type)))
				goto check_next_ie;
			/*check version...*/
			memcpy((u8 *)&val16, (buf + 6), sizeof(val16));
			le16_to_cpus(&val16);
			if (val16 != 0x0001)
				goto check_next_ie;
			*wpa_ie_len = *(buf + 1);
			return buf;
		}
		*wpa_ie_len = 0;
		return NULL;
check_next_ie:
		limit = limit - (buf - ie) - 2 - len;
		if (limit <= 0)
			break;
		buf += (2 + len);
	}
	*wpa_ie_len = 0;
	return NULL;
}