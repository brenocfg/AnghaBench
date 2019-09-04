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
struct ishtp_device {int /*<<< orphan*/  cl_list_lock; } ;
struct ishtp_cl {struct ishtp_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ishtp_cl_free_rx_ring (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_cl_free_tx_ring (struct ishtp_cl*) ; 
 int /*<<< orphan*/  kfree (struct ishtp_cl*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void	ishtp_cl_free(struct ishtp_cl *cl)
{
	struct ishtp_device *dev;
	unsigned long flags;

	if (!cl)
		return;

	dev = cl->dev;
	if (!dev)
		return;

	spin_lock_irqsave(&dev->cl_list_lock, flags);
	ishtp_cl_free_rx_ring(cl);
	ishtp_cl_free_tx_ring(cl);
	kfree(cl);
	spin_unlock_irqrestore(&dev->cl_list_lock, flags);
}