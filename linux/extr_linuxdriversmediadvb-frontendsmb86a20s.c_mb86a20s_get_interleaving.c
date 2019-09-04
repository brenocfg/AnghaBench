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
struct mb86a20s_state {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned char*) ; 
 int EINVAL ; 
 int mb86a20s_readreg (struct mb86a20s_state*,int) ; 
 int mb86a20s_writereg (struct mb86a20s_state*,int,unsigned char) ; 

__attribute__((used)) static int mb86a20s_get_interleaving(struct mb86a20s_state *state,
				     unsigned layer)
{
	int rc;
	int interleaving[] = {
		0, 1, 2, 4, 8
	};

	static unsigned char reg[] = {
		[0] = 0x88,	/* Layer A */
		[1] = 0x8c,	/* Layer B */
		[2] = 0x90,	/* Layer C */
	};

	if (layer >= ARRAY_SIZE(reg))
		return -EINVAL;
	rc = mb86a20s_writereg(state, 0x6d, reg[layer]);
	if (rc < 0)
		return rc;
	rc = mb86a20s_readreg(state, 0x6e);
	if (rc < 0)
		return rc;

	return interleaving[(rc >> 4) & 0x07];
}