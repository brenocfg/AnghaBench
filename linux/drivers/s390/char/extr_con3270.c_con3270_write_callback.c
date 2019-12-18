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
struct raw3270_request {scalar_t__ view; } ;
struct con3270 {int /*<<< orphan*/  write; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw3270_request_reset (struct raw3270_request*) ; 
 int /*<<< orphan*/  xchg (int /*<<< orphan*/ *,struct raw3270_request*) ; 

__attribute__((used)) static void
con3270_write_callback(struct raw3270_request *rq, void *data)
{
	raw3270_request_reset(rq);
	xchg(&((struct con3270 *) rq->view)->write, rq);
}