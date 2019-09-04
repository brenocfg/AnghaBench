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
struct dvb_frontend_private {int wakeup; int /*<<< orphan*/  wait_queue; } ;
struct dvb_frontend {struct dvb_frontend_private* frontend_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dvb_frontend_wakeup(struct dvb_frontend *fe)
{
	struct dvb_frontend_private *fepriv = fe->frontend_priv;

	fepriv->wakeup = 1;
	wake_up_interruptible(&fepriv->wait_queue);
}