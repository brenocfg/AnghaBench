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
struct mv_xor_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XOR_CONFIG (struct mv_xor_chan*) ; 
 int XOR_DESCRIPTOR_SWAP ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv_chan_set_mode(struct mv_xor_chan *chan,
			     u32 op_mode)
{
	u32 config = readl_relaxed(XOR_CONFIG(chan));

	config &= ~0x7;
	config |= op_mode;

#if defined(__BIG_ENDIAN)
	config |= XOR_DESCRIPTOR_SWAP;
#else
	config &= ~XOR_DESCRIPTOR_SWAP;
#endif

	writel_relaxed(config, XOR_CONFIG(chan));
}