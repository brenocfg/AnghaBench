#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  fmt; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;
struct channel_program {int /*<<< orphan*/  guest_cp; TYPE_2__ orb; int /*<<< orphan*/  mdev; } ;
struct ccwchain {int /*<<< orphan*/  ch_ccw; int /*<<< orphan*/  ch_iova; } ;
struct ccw1 {int dummy; } ;

/* Variables and functions */
 int CCWCHAIN_LEN_MAX ; 
 int ENOMEM ; 
 struct ccwchain* ccwchain_alloc (struct channel_program*,int) ; 
 int ccwchain_calc_length (int /*<<< orphan*/ ,struct channel_program*) ; 
 int /*<<< orphan*/  ccwchain_free (struct ccwchain*) ; 
 int ccwchain_loop_tic (struct ccwchain*,struct channel_program*) ; 
 int /*<<< orphan*/  convert_ccw0_to_ccw1 (int /*<<< orphan*/ ,int) ; 
 int copy_from_iova (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ccwchain_handle_ccw(u32 cda, struct channel_program *cp)
{
	struct ccwchain *chain;
	int len, ret;

	/* Copy 2K (the most we support today) of possible CCWs */
	len = copy_from_iova(cp->mdev, cp->guest_cp, cda,
			     CCWCHAIN_LEN_MAX * sizeof(struct ccw1));
	if (len)
		return len;

	/* Convert any Format-0 CCWs to Format-1 */
	if (!cp->orb.cmd.fmt)
		convert_ccw0_to_ccw1(cp->guest_cp, CCWCHAIN_LEN_MAX);

	/* Count the CCWs in the current chain */
	len = ccwchain_calc_length(cda, cp);
	if (len < 0)
		return len;

	/* Need alloc a new chain for this one. */
	chain = ccwchain_alloc(cp, len);
	if (!chain)
		return -ENOMEM;
	chain->ch_iova = cda;

	/* Copy the actual CCWs into the new chain */
	memcpy(chain->ch_ccw, cp->guest_cp, len * sizeof(struct ccw1));

	/* Loop for tics on this new chain. */
	ret = ccwchain_loop_tic(chain, cp);

	if (ret)
		ccwchain_free(chain);

	return ret;
}