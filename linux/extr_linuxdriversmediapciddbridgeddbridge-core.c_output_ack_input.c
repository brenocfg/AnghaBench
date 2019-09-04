#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ddb_output {TYPE_2__* dma; } ;
struct ddb_input {int /*<<< orphan*/  dma; TYPE_1__* port; } ;
struct TYPE_4__ {int /*<<< orphan*/  stat; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BUFFER_ACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddbwritel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void output_ack_input(struct ddb_output *output,
			     struct ddb_input *input)
{
	ddbwritel(input->port->dev,
		  output->dma->stat, DMA_BUFFER_ACK(input->dma));
}