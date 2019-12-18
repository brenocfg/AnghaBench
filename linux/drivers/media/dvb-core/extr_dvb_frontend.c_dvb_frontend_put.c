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
struct TYPE_2__ {int /*<<< orphan*/  (* detach ) (struct dvb_frontend*) ;} ;
struct dvb_frontend {int /*<<< orphan*/  refcount; scalar_t__ frontend_priv; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dvb_frontend_free (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dvb_frontend_free ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*) ; 

__attribute__((used)) static void dvb_frontend_put(struct dvb_frontend *fe)
{
	/* call detach before dropping the reference count */
	if (fe->ops.detach)
		fe->ops.detach(fe);
	/*
	 * Check if the frontend was registered, as otherwise
	 * kref was not initialized yet.
	 */
	if (fe->frontend_priv)
		kref_put(&fe->refcount, dvb_frontend_free);
	else
		__dvb_frontend_free(fe);
}