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
struct mc44s803_priv {int dummy; } ;
struct dvb_frontend {struct mc44s803_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mc44s803_priv*) ; 

__attribute__((used)) static void mc44s803_release(struct dvb_frontend *fe)
{
	struct mc44s803_priv *priv = fe->tuner_priv;

	fe->tuner_priv = NULL;
	kfree(priv);
}