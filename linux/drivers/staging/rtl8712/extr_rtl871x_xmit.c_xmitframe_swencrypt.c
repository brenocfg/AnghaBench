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
struct pkt_attrib {int encrypt; scalar_t__ bswenc; } ;
struct xmit_frame {struct pkt_attrib attrib; } ;
struct _adapter {int dummy; } ;
typedef  int /*<<< orphan*/  sint ;

/* Variables and functions */
#define  _AES_ 131 
 int /*<<< orphan*/  _SUCCESS ; 
#define  _TKIP_ 130 
#define  _WEP104_ 129 
#define  _WEP40_ 128 
 int /*<<< orphan*/  r8712_aes_encrypt (struct _adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r8712_tkip_encrypt (struct _adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r8712_wep_encrypt (struct _adapter*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static sint xmitframe_swencrypt(struct _adapter *padapter,
				struct xmit_frame *pxmitframe)
{
	struct pkt_attrib	*pattrib = &pxmitframe->attrib;

	if (pattrib->bswenc) {
		switch (pattrib->encrypt) {
		case _WEP40_:
		case _WEP104_:
			r8712_wep_encrypt(padapter, (u8 *)pxmitframe);
			break;
		case _TKIP_:
			r8712_tkip_encrypt(padapter, (u8 *)pxmitframe);
			break;
		case _AES_:
			r8712_aes_encrypt(padapter, (u8 *)pxmitframe);
			break;
		default:
				break;
		}
	}
	return _SUCCESS;
}