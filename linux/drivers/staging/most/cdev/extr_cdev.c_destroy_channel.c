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
struct comp_channel {int /*<<< orphan*/  fifo; int /*<<< orphan*/  devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  minor_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 TYPE_1__ comp ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct comp_channel*) ; 

__attribute__((used)) static void destroy_channel(struct comp_channel *c)
{
	ida_simple_remove(&comp.minor_id, MINOR(c->devno));
	kfifo_free(&c->fifo);
	kfree(c);
}