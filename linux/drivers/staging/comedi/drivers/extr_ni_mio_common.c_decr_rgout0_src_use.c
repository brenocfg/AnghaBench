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
struct ni_private {scalar_t__ rgout0_usage; int /*<<< orphan*/  routing_tables; } ;
struct comedi_device {struct ni_private* private; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int /*<<< orphan*/  CR_CHAN (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NI_RGOUT0 ; 
 scalar_t__ get_rgout0_reg (struct comedi_device*) ; 
 scalar_t__ ni_lookup_route_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_rgout0_reg (int /*<<< orphan*/ ,struct comedi_device*) ; 

__attribute__((used)) static int decr_rgout0_src_use(int src, struct comedi_device *dev)
{
	struct ni_private *devpriv = dev->private;
	s8 reg = ni_lookup_route_register(CR_CHAN(src), NI_RGOUT0,
					  &devpriv->routing_tables);

	if (devpriv->rgout0_usage > 0 && get_rgout0_reg(dev) == reg) {
		--devpriv->rgout0_usage;
		if (!devpriv->rgout0_usage)
			set_rgout0_reg(0, dev); /* ok default? */
		return 0;
	}
	return -EINVAL;
}