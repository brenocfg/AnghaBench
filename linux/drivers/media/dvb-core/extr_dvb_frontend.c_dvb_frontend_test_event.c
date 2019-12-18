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
struct dvb_frontend_private {int /*<<< orphan*/  sem; } ;
struct dvb_fe_events {scalar_t__ eventw; scalar_t__ eventr; } ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dvb_frontend_test_event(struct dvb_frontend_private *fepriv,
				   struct dvb_fe_events *events)
{
	int ret;

	up(&fepriv->sem);
	ret = events->eventw != events->eventr;
	down(&fepriv->sem);

	return ret;
}