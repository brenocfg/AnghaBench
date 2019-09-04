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
 int EINVAL ; 
 int nfp_decode_basic (int /*<<< orphan*/ ,int*,int,int,int,int,int) ; 

__attribute__((used)) static int nfp_encode_basic_qdr(u64 addr, int dest_island, int cpp_tgt,
				int mode, bool addr40, int isld1, int isld0)
{
	int v, ret;

	/* Full Island ID and channel bits overlap? */
	ret = nfp_decode_basic(addr, &v, cpp_tgt, mode, addr40, isld1, isld0);
	if (ret)
		return ret;

	/* The current address won't go where expected? */
	if (dest_island != -1 && dest_island != v)
		return -EINVAL;

	/* If dest_island was -1, we don't care where it goes. */
	return 0;
}