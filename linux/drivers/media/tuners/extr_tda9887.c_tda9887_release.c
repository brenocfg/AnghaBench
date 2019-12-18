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
struct tda9887_priv {int dummy; } ;
struct dvb_frontend {struct tda9887_priv* analog_demod_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  hybrid_tuner_release_state (struct tda9887_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tda9887_list_mutex ; 

__attribute__((used)) static void tda9887_release(struct dvb_frontend *fe)
{
	struct tda9887_priv *priv = fe->analog_demod_priv;

	mutex_lock(&tda9887_list_mutex);

	if (priv)
		hybrid_tuner_release_state(priv);

	mutex_unlock(&tda9887_list_mutex);

	fe->analog_demod_priv = NULL;
}