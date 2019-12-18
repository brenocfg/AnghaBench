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
struct vp702x_fe_state {int dummy; } ;
struct dvb_frontend {struct vp702x_fe_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  vp702x_fe_refresh_state (struct vp702x_fe_state*) ; 

__attribute__((used)) static int vp702x_fe_read_unc_blocks(struct dvb_frontend* fe, u32 *unc)
{
	struct vp702x_fe_state *st = fe->demodulator_priv;
	vp702x_fe_refresh_state(st);
	*unc = 0;
	return 0;
}