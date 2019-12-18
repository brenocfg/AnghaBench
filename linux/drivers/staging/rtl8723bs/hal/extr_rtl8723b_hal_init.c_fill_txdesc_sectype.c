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
struct pkt_attrib {int encrypt; int /*<<< orphan*/  bswenc; } ;

/* Variables and functions */
#define  _AES_ 133 
#define  _NO_PRIVACY_ 132 
#define  _TKIP_ 131 
#define  _TKIP_WTMIC_ 130 
#define  _WEP104_ 129 
#define  _WEP40_ 128 

__attribute__((used)) static u8 fill_txdesc_sectype(struct pkt_attrib *pattrib)
{
	u8 sectype = 0;
	if ((pattrib->encrypt > 0) && !pattrib->bswenc) {
		switch (pattrib->encrypt) {
		/*  SEC_TYPE */
		case _WEP40_:
		case _WEP104_:
		case _TKIP_:
		case _TKIP_WTMIC_:
			sectype = 1;
			break;

		case _AES_:
			sectype = 3;
			break;

		case _NO_PRIVACY_:
		default:
			break;
		}
	}
	return sectype;
}