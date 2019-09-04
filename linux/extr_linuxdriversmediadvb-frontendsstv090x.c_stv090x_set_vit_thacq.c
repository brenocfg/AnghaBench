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
struct stv090x_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_ERROR ; 
 scalar_t__ STV090x_WRITE_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VTH12 ; 
 int /*<<< orphan*/  VTH23 ; 
 int /*<<< orphan*/  VTH34 ; 
 int /*<<< orphan*/  VTH56 ; 
 int /*<<< orphan*/  VTH67 ; 
 int /*<<< orphan*/  VTH78 ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int stv090x_set_vit_thacq(struct stv090x_state *state)
{
	if (STV090x_WRITE_DEMOD(state, VTH12, 0x96) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, VTH23, 0x64) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, VTH34, 0x36) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, VTH56, 0x23) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, VTH67, 0x1e) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, VTH78, 0x19) < 0)
		goto err;
	return 0;
err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}