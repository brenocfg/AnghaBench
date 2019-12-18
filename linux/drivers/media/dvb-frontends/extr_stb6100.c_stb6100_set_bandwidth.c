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
struct stb6100_state {int dummy; } ;
struct dvb_frontend {struct stb6100_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  STB6100_F ; 
 int /*<<< orphan*/  STB6100_FCCK ; 
 int STB6100_FCCK_FCCK ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stb6100_write_reg (struct stb6100_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int stb6100_set_bandwidth(struct dvb_frontend *fe, u32 bandwidth)
{
	u32 tmp;
	int rc;
	struct stb6100_state *state = fe->tuner_priv;

	dprintk(verbose, FE_DEBUG, 1, "set bandwidth to %u Hz", bandwidth);

	bandwidth /= 2; /* ZIF */

	if (bandwidth >= 36000000)	/* F[4:0] BW/2 max =31+5=36 mhz for F=31	*/
		tmp = 31;
	else if (bandwidth <= 5000000)	/* bw/2 min = 5Mhz for F=0			*/
		tmp = 0;
	else				/* if 5 < bw/2 < 36				*/
		tmp = (bandwidth + 500000) / 1000000 - 5;

	/* Turn on LPF bandwidth setting clock control,
	 * set bandwidth, wait 10ms, turn off.
	 */
	rc = stb6100_write_reg(state, STB6100_FCCK, 0x0d | STB6100_FCCK_FCCK);
	if (rc < 0)
		return rc;
	rc = stb6100_write_reg(state, STB6100_F, 0xc0 | tmp);
	if (rc < 0)
		return rc;

	msleep(5);  /*  This is dangerous as another (related) thread may start */

	rc = stb6100_write_reg(state, STB6100_FCCK, 0x0d);
	if (rc < 0)
		return rc;

	msleep(10);  /*  This is dangerous as another (related) thread may start */

	return 0;
}