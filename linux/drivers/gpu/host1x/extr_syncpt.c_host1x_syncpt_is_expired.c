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
typedef  scalar_t__ u32 ;
struct host1x_syncpt {int /*<<< orphan*/  max_val; int /*<<< orphan*/  min_val; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host1x_syncpt_client_managed (struct host1x_syncpt*) ; 
 int /*<<< orphan*/  smp_rmb () ; 

bool host1x_syncpt_is_expired(struct host1x_syncpt *sp, u32 thresh)
{
	u32 current_val;
	u32 future_val;

	smp_rmb();

	current_val = (u32)atomic_read(&sp->min_val);
	future_val = (u32)atomic_read(&sp->max_val);

	/* Note the use of unsigned arithmetic here (mod 1<<32).
	 *
	 * c = current_val = min_val	= the current value of the syncpoint.
	 * t = thresh			= the value we are checking
	 * f = future_val  = max_val	= the value c will reach when all
	 *				  outstanding increments have completed.
	 *
	 * Note that c always chases f until it reaches f.
	 *
	 * Dtf = (f - t)
	 * Dtc = (c - t)
	 *
	 *  Consider all cases:
	 *
	 *	A) .....c..t..f.....	Dtf < Dtc	need to wait
	 *	B) .....c.....f..t..	Dtf > Dtc	expired
	 *	C) ..t..c.....f.....	Dtf > Dtc	expired	   (Dct very large)
	 *
	 *  Any case where f==c: always expired (for any t).	Dtf == Dcf
	 *  Any case where t==c: always expired (for any f).	Dtf >= Dtc (because Dtc==0)
	 *  Any case where t==f!=c: always wait.		Dtf <  Dtc (because Dtf==0,
	 *							Dtc!=0)
	 *
	 *  Other cases:
	 *
	 *	A) .....t..f..c.....	Dtf < Dtc	need to wait
	 *	A) .....f..c..t.....	Dtf < Dtc	need to wait
	 *	A) .....f..t..c.....	Dtf > Dtc	expired
	 *
	 *   So:
	 *	   Dtf >= Dtc implies EXPIRED	(return true)
	 *	   Dtf <  Dtc implies WAIT	(return false)
	 *
	 * Note: If t is expired then we *cannot* wait on it. We would wait
	 * forever (hang the system).
	 *
	 * Note: do NOT get clever and remove the -thresh from both sides. It
	 * is NOT the same.
	 *
	 * If future valueis zero, we have a client managed sync point. In that
	 * case we do a direct comparison.
	 */
	if (!host1x_syncpt_client_managed(sp))
		return future_val - thresh >= current_val - thresh;
	else
		return (s32)(current_val - thresh) >= 0;
}