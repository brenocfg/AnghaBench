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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  AT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int NFP_CPP_ACTION_RW ; 
 int NFP_CPP_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P64 ; 

__attribute__((used)) static int nfp6000_nbi_dma(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(0, 0,   0, P64);	/* ReadNbiDma */
	AT(1, 0,   P64, 0);	/* WriteNbiDma */
	AT(NFP_CPP_ACTION_RW, 0, P64, P64);
	default:
		return -EINVAL;
	}
}