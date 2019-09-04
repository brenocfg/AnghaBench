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

/* Variables and functions */
 int B44_MAX_PATTERNS ; 
 int B44_PATTERN_SIZE ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int b44_magic_pattern(u8 *macaddr, u8 *ppattern, u8 *pmask, int offset)
{
	int magicsync = 6;
	int k, j, len = offset;
	int ethaddr_bytes = ETH_ALEN;

	memset(ppattern + offset, 0xff, magicsync);
	for (j = 0; j < magicsync; j++)
		set_bit(len++, (unsigned long *) pmask);

	for (j = 0; j < B44_MAX_PATTERNS; j++) {
		if ((B44_PATTERN_SIZE - len) >= ETH_ALEN)
			ethaddr_bytes = ETH_ALEN;
		else
			ethaddr_bytes = B44_PATTERN_SIZE - len;
		if (ethaddr_bytes <=0)
			break;
		for (k = 0; k< ethaddr_bytes; k++) {
			ppattern[offset + magicsync +
				(j * ETH_ALEN) + k] = macaddr[k];
			set_bit(len++, (unsigned long *) pmask);
		}
	}
	return len - 1;
}