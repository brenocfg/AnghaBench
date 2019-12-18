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
struct helene_priv {int frequency; } ;
struct dvb_frontend {struct helene_priv* tuner_priv; } ;

/* Variables and functions */

__attribute__((used)) static int helene_get_frequency(struct dvb_frontend *fe, u32 *frequency)
{
	struct helene_priv *priv = fe->tuner_priv;

	*frequency = priv->frequency * 1000;
	return 0;
}