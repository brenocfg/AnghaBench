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
typedef  int /*<<< orphan*/  u32 ;
struct ts2020_priv {int /*<<< orphan*/  frequency_khz; } ;
struct dvb_frontend {struct ts2020_priv* tuner_priv; } ;

/* Variables and functions */

__attribute__((used)) static int ts2020_get_frequency(struct dvb_frontend *fe, u32 *frequency)
{
	struct ts2020_priv *priv = fe->tuner_priv;

	*frequency = priv->frequency_khz;
	return 0;
}