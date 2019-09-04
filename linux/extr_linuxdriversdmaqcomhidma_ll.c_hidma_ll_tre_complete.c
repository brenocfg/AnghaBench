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
struct hidma_tre {int /*<<< orphan*/  data; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ) ;} ;
struct hidma_lldev {int /*<<< orphan*/  handoff_fifo; } ;

/* Variables and functions */
 scalar_t__ kfifo_out (int /*<<< orphan*/ *,struct hidma_tre**,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hidma_ll_tre_complete(unsigned long arg)
{
	struct hidma_lldev *lldev = (struct hidma_lldev *)arg;
	struct hidma_tre *tre;

	while (kfifo_out(&lldev->handoff_fifo, &tre, 1)) {
		/* call the user if it has been read by the hardware */
		if (tre->callback)
			tre->callback(tre->data);
	}
}