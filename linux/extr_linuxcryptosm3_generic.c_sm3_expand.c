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
typedef  unsigned int u32 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 unsigned int get_unaligned_be32 (int /*<<< orphan*/ *) ; 
 unsigned int p1 (unsigned int) ; 
 unsigned int rol32 (unsigned int,int) ; 

__attribute__((used)) static void sm3_expand(u32 *t, u32 *w, u32 *wt)
{
	int i;
	unsigned int tmp;

	/* load the input */
	for (i = 0; i <= 15; i++)
		w[i] = get_unaligned_be32((__u32 *)t + i);

	for (i = 16; i <= 67; i++) {
		tmp = w[i - 16] ^ w[i - 9] ^ rol32(w[i - 3], 15);
		w[i] = p1(tmp) ^ (rol32(w[i - 13], 7)) ^ w[i - 6];
	}

	for (i = 0; i <= 63; i++)
		wt[i] = w[i] ^ w[i + 4];
}