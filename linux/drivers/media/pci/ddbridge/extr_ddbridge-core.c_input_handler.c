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
struct ddb_input {struct ddb_dma* dma; } ;
struct ddb_dma {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  ddb_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void input_handler(void *data)
{
	struct ddb_input *input = (struct ddb_input *)data;
	struct ddb_dma *dma = input->dma;

	queue_work(ddb_wq, &dma->work);
}