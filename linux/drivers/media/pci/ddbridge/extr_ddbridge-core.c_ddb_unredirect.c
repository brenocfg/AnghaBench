#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ddb_port {TYPE_6__* output; struct ddb_input** input; } ;
struct ddb_output {int /*<<< orphan*/  dma; TYPE_4__* port; } ;
struct ddb_input {struct ddb_output* redo; struct ddb_input* redi; int /*<<< orphan*/  dma; TYPE_5__* port; } ;
struct TYPE_12__ {struct ddb_input* redi; TYPE_1__* dma; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {TYPE_3__** input; TYPE_2__* output; } ;
struct TYPE_9__ {struct ddb_input* redi; } ;
struct TYPE_8__ {struct ddb_input* redi; } ;
struct TYPE_7__ {scalar_t__ running; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ddb_redirect_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddb_set_dma_table (struct ddb_input*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redirect_lock ; 

__attribute__((used)) static int ddb_unredirect(struct ddb_port *port)
{
	struct ddb_input *oredi, *iredi = NULL;
	struct ddb_output *iredo = NULL;

	/* dev_info(port->dev->dev,
	 * "unredirect %d.%d\n", port->dev->nr, port->nr);
	 */
	mutex_lock(&redirect_lock);
	if (port->output->dma->running) {
		mutex_unlock(&redirect_lock);
		return -EBUSY;
	}
	oredi = port->output->redi;
	if (!oredi)
		goto done;
	if (port->input[0]) {
		iredi = port->input[0]->redi;
		iredo = port->input[0]->redo;

		if (iredo) {
			iredo->port->output->redi = oredi;
			if (iredo->port->input[0]) {
				iredo->port->input[0]->redi = iredi;
				ddb_redirect_dma(oredi->port->dev,
						 oredi->dma, iredo->dma);
			}
			port->input[0]->redo = NULL;
			ddb_set_dma_table(port->input[0]);
		}
		oredi->redi = iredi;
		port->input[0]->redi = NULL;
	}
	oredi->redo = NULL;
	port->output->redi = NULL;

	ddb_set_dma_table(oredi);
done:
	mutex_unlock(&redirect_lock);
	return 0;
}