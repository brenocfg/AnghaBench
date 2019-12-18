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
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int PRISM2_PDA_SIZE ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prism2_pda_ok(u8 *buf)
{
	__le16 *pda = (__le16 *) buf;
	int pos;
	u16 len, pdr;

	if (buf[0] == 0xff && buf[1] == 0x00 && buf[2] == 0xff &&
	    buf[3] == 0x00)
		return 0;

	pos = 0;
	while (pos + 1 < PRISM2_PDA_SIZE / 2) {
		len = le16_to_cpu(pda[pos]);
		pdr = le16_to_cpu(pda[pos + 1]);
		if (len == 0 || pos + len > PRISM2_PDA_SIZE / 2)
			return 0;

		if (pdr == 0x0000 && len == 2) {
			/* PDA end found */
			return 1;
		}

		pos += len + 1;
	}

	return 0;
}