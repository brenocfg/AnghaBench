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
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */

__attribute__((used)) static void xdi_xlog_ind(byte Adapter,
			 byte Id,
			 byte Ch,
			 byte Ind,
			 byte rnr_valid,
			 byte rnr,
			 byte type) {
#if defined(XDI_USE_XLOG)
	word LogInfo[4];
	PUT_WORD(&LogInfo[0], ((word)Adapter | (word)(xdi_xlog_sec++ << 8)));
	PUT_WORD(&LogInfo[1], ((word)Id | (word)(Ch << 8)));
	PUT_WORD(&LogInfo[2], ((word)Ind | (word)(type << 8)));
	PUT_WORD(&LogInfo[3], ((word)rnr | (word)(rnr_valid << 8)));
	xdi_xlog((byte *)&LogInfo[0], 222, sizeof(LogInfo));
#endif
}