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
 int DES_BLOCK_SIZE ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  crypto_inc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned int __ctrblk_init(u8 *ctrptr, u8 *iv, unsigned int nbytes)
{
	unsigned int i, n;

	/* align to block size, max. PAGE_SIZE */
	n = (nbytes > PAGE_SIZE) ? PAGE_SIZE : nbytes & ~(DES_BLOCK_SIZE - 1);
	memcpy(ctrptr, iv, DES_BLOCK_SIZE);
	for (i = (n / DES_BLOCK_SIZE) - 1; i > 0; i--) {
		memcpy(ctrptr + DES_BLOCK_SIZE, ctrptr, DES_BLOCK_SIZE);
		crypto_inc(ctrptr + DES_BLOCK_SIZE, DES_BLOCK_SIZE);
		ctrptr += DES_BLOCK_SIZE;
	}
	return n;
}