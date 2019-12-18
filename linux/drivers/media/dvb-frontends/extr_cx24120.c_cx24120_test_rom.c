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
struct cx24120_state {int dummy; } ;

/* Variables and functions */
 int cx24120_readreg (struct cx24120_state*,int) ; 
 int cx24120_writereg (struct cx24120_state*,int,int) ; 

__attribute__((used)) static int cx24120_test_rom(struct cx24120_state *state)
{
	int err, ret;

	err = cx24120_readreg(state, 0xfd);
	if (err & 4) {
		ret = cx24120_readreg(state, 0xdf) & 0xfe;
		err = cx24120_writereg(state, 0xdf, ret);
	}
	return err;
}