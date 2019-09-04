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
struct dvb_fe_events {int /*<<< orphan*/  mtx; int /*<<< orphan*/  eventw; int /*<<< orphan*/  eventr; } ;
struct dvb_frontend_private {struct dvb_fe_events events; } ;
struct dvb_frontend {struct dvb_frontend_private* frontend_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dvb_frontend_clear_events(struct dvb_frontend *fe)
{
	struct dvb_frontend_private *fepriv = fe->frontend_priv;
	struct dvb_fe_events *events = &fepriv->events;

	mutex_lock(&events->mtx);
	events->eventr = events->eventw;
	mutex_unlock(&events->mtx);
}