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
 int /*<<< orphan*/  MODCODLST0 ; 
 int /*<<< orphan*/  MODCODLST1 ; 
 int /*<<< orphan*/  MODCODLST2 ; 
 int /*<<< orphan*/  MODCODLST3 ; 
 int /*<<< orphan*/  MODCODLST4 ; 
 int /*<<< orphan*/  MODCODLST5 ; 
 int /*<<< orphan*/  MODCODLST6 ; 
 int /*<<< orphan*/  MODCODLST7 ; 
 int /*<<< orphan*/  MODCODLST8 ; 
 int /*<<< orphan*/  MODCODLST9 ; 
 int /*<<< orphan*/  MODCODLSTA ; 
 int /*<<< orphan*/  MODCODLSTB ; 
 int /*<<< orphan*/  MODCODLSTC ; 
 int /*<<< orphan*/  MODCODLSTD ; 
 int /*<<< orphan*/  MODCODLSTE ; 
 int /*<<< orphan*/  MODCODLSTF ; 
 scalar_t__ STV090x_WRITE_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int stv090x_activate_modcod_single(struct stv090x_state *state)
{

	if (STV090x_WRITE_DEMOD(state, MODCODLST0, 0xff) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, MODCODLST1, 0xf0) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, MODCODLST2, 0x00) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, MODCODLST3, 0x00) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, MODCODLST4, 0x00) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, MODCODLST5, 0x00) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, MODCODLST6, 0x00) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, MODCODLST7, 0x00) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, MODCODLST8, 0x00) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, MODCODLST9, 0x00) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, MODCODLSTA, 0x00) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, MODCODLSTB, 0x00) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, MODCODLSTC, 0x00) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, MODCODLSTD, 0x00) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, MODCODLSTE, 0x00) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, MODCODLSTF, 0x0f) < 0)
		goto err;

	return 0;

err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}