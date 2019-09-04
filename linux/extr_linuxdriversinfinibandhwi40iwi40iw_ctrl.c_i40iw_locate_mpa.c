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

/* Variables and functions */
 int /*<<< orphan*/  I40IW_MAC_HLEN ; 

__attribute__((used)) static u8 *i40iw_locate_mpa(u8 *pkt)
{
	/* skip over ethernet header */
	pkt += I40IW_MAC_HLEN;

	/* Skip over IP and TCP headers */
	pkt += 4 * (pkt[0] & 0x0f);
	pkt += 4 * ((pkt[12] >> 4) & 0x0f);
	return pkt;
}