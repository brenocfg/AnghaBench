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
struct qib_flash {int if_length; int if_csum; } ;

/* Variables and functions */

__attribute__((used)) static u8 flash_csum(struct qib_flash *ifp, int adjust)
{
	u8 *ip = (u8 *) ifp;
	u8 csum = 0, len;

	/*
	 * Limit length checksummed to max length of actual data.
	 * Checksum of erased eeprom will still be bad, but we avoid
	 * reading past the end of the buffer we were passed.
	 */
	len = ifp->if_length;
	if (len > sizeof(struct qib_flash))
		len = sizeof(struct qib_flash);
	while (len--)
		csum += *ip++;
	csum -= ifp->if_csum;
	csum = ~csum;
	if (adjust)
		ifp->if_csum = csum;

	return csum;
}