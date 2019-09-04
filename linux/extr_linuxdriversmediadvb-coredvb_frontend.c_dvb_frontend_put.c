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
struct dvb_frontend {int /*<<< orphan*/  refcount; scalar_t__ frontend_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dvb_frontend_free (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dvb_frontend_free ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dvb_frontend_put(struct dvb_frontend *fe)
{
	/*
	 * Check if the frontend was registered, as otherwise
	 * kref was not initialized yet.
	 */
	if (fe->frontend_priv)
		kref_put(&fe->refcount, dvb_frontend_free);
	else
		__dvb_frontend_free(fe);
}