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
struct scpi_xfer {int /*<<< orphan*/  node; } ;
struct scpi_chan {int /*<<< orphan*/  xfers_lock; int /*<<< orphan*/  xfers_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_scpi_xfer(struct scpi_xfer *t, struct scpi_chan *ch)
{
	mutex_lock(&ch->xfers_lock);
	list_add_tail(&t->node, &ch->xfers_list);
	mutex_unlock(&ch->xfers_lock);
}