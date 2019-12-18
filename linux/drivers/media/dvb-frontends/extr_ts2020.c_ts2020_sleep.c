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
typedef  int u8 ;
struct ts2020_priv {scalar_t__ tuner; int /*<<< orphan*/  stat_work; int /*<<< orphan*/  dont_poll; int /*<<< orphan*/  regmap; } ;
struct dvb_frontend {struct ts2020_priv* tuner_priv; } ;

/* Variables and functions */
 scalar_t__ TS2020_M88TS2020 ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ts2020_sleep(struct dvb_frontend *fe)
{
	struct ts2020_priv *priv = fe->tuner_priv;
	int ret;
	u8 u8tmp;

	if (priv->tuner == TS2020_M88TS2020)
		u8tmp = 0x0a; /* XXX: probably wrong */
	else
		u8tmp = 0x00;

	ret = regmap_write(priv->regmap, u8tmp, 0x00);
	if (ret < 0)
		return ret;

	/* stop statistics polling */
	if (!priv->dont_poll)
		cancel_delayed_work_sync(&priv->stat_work);
	return 0;
}