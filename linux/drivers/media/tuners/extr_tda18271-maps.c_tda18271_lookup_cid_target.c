#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tda18271_priv {int dummy; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;
struct TYPE_2__ {int rfmax; int /*<<< orphan*/  limit; int /*<<< orphan*/  target; } ;

/* Variables and functions */
 TYPE_1__* tda18271_cid_target ; 
 int /*<<< orphan*/  tda_map (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tda18271_lookup_cid_target(struct dvb_frontend *fe,
			       u32 *freq, u8 *cid_target, u16 *count_limit)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	int i = 0;

	while ((tda18271_cid_target[i].rfmax * 1000) < *freq) {
		if (tda18271_cid_target[i + 1].rfmax == 0)
			break;
		i++;
	}
	*cid_target  = tda18271_cid_target[i].target;
	*count_limit = tda18271_cid_target[i].limit;

	tda_map("(%d) cid_target = %02x, count_limit = %d\n", i,
		tda18271_cid_target[i].target, tda18271_cid_target[i].limit);

	return 0;
}