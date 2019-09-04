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
struct subch_data_s {int /*<<< orphan*/  sd_subch; int /*<<< orphan*/  sd_nasid; } ;
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGI_UART_VECTOR ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct subch_data_s*) ; 
 int ia64_sn_irtr_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct subch_data_s*) ; 

__attribute__((used)) static int
scdrv_release(struct inode *inode, struct file *file)
{
	struct subch_data_s *sd = (struct subch_data_s *) file->private_data;
	int rv;

	/* free the interrupt */
	free_irq(SGI_UART_VECTOR, sd);

	/* ask SAL to close the subchannel */
	rv = ia64_sn_irtr_close(sd->sd_nasid, sd->sd_subch);

	kfree(sd);
	return rv;
}