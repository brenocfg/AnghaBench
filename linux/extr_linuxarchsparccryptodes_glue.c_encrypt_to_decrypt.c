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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int DES_EXPKEY_WORDS ; 

__attribute__((used)) static void encrypt_to_decrypt(u64 *d, const u64 *e)
{
	const u64 *s = e + (DES_EXPKEY_WORDS / 2) - 1;
	int i;

	for (i = 0; i < DES_EXPKEY_WORDS / 2; i++)
		*d++ = *s--;
}