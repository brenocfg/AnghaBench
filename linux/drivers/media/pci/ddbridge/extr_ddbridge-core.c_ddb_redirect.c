#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ddb_port {TYPE_2__* output; struct ddb_input** input; } ;
struct ddb_input {TYPE_3__* dma; TYPE_1__* port; TYPE_2__* redo; struct ddb_input* redi; } ;
struct ddb {struct ddb_input* input; struct ddb_port* port; int /*<<< orphan*/  has_dma; } ;
struct TYPE_8__ {scalar_t__ running; } ;
struct TYPE_7__ {scalar_t__ running; } ;
struct TYPE_6__ {TYPE_4__* dma; struct ddb_input* redi; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  ddb_redirect_dma (int /*<<< orphan*/ ,TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ ddb_unredirect (struct ddb_port*) ; 
 struct ddb** ddbs ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redirect_lock ; 

__attribute__((used)) static int ddb_redirect(u32 i, u32 p)
{
	struct ddb *idev = ddbs[(i >> 4) & 0x3f];
	struct ddb_input *input, *input2;
	struct ddb *pdev = ddbs[(p >> 4) & 0x3f];
	struct ddb_port *port;

	if (!idev || !pdev)
		return -EINVAL;
	if (!idev->has_dma || !pdev->has_dma)
		return -EINVAL;

	port = &pdev->port[p & 0x0f];
	if (!port->output)
		return -EINVAL;
	if (ddb_unredirect(port))
		return -EBUSY;

	if (i == 8)
		return 0;

	input = &idev->input[i & 7];
	if (!input)
		return -EINVAL;

	mutex_lock(&redirect_lock);
	if (port->output->dma->running || input->dma->running) {
		mutex_unlock(&redirect_lock);
		return -EBUSY;
	}
	input2 = port->input[0];
	if (input2) {
		if (input->redi) {
			input2->redi = input->redi;
			input->redi = NULL;
		} else {
			input2->redi = input;
		}
	}
	input->redo = port->output;
	port->output->redi = input;

	ddb_redirect_dma(input->port->dev, input->dma, port->output->dma);
	mutex_unlock(&redirect_lock);
	return 0;
}