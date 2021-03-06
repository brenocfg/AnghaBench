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
struct ocrdma_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocrdma_dispatch_port_error (struct ocrdma_dev*) ; 
 int /*<<< orphan*/  ocrdma_remove (struct ocrdma_dev*) ; 

__attribute__((used)) static void ocrdma_shutdown(struct ocrdma_dev *dev)
{
	ocrdma_dispatch_port_error(dev);
	ocrdma_remove(dev);
}