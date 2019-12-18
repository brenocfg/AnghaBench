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
struct ni_private {int /*<<< orphan*/  mite_channel_lock; int /*<<< orphan*/  soft_reg_copy_lock; int /*<<< orphan*/  window_lock; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ni_private* comedi_alloc_devpriv (struct comedi_device*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ni_alloc_private(struct comedi_device *dev)
{
	struct ni_private *devpriv;

	devpriv = comedi_alloc_devpriv(dev, sizeof(*devpriv));
	if (!devpriv)
		return -ENOMEM;

	spin_lock_init(&devpriv->window_lock);
	spin_lock_init(&devpriv->soft_reg_copy_lock);
	spin_lock_init(&devpriv->mite_channel_lock);

	return 0;
}