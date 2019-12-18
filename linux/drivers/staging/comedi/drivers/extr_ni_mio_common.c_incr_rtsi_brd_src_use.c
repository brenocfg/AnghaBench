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
struct ni_private {int /*<<< orphan*/ * rtsi_shared_mux_usage; int /*<<< orphan*/  routing_tables; } ;
struct comedi_device {struct ni_private* private; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int /*<<< orphan*/  CR_CHAN (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int NI_RTSI_BRD (int) ; 
 int NUM_RTSI_SHARED_MUXS ; 
 scalar_t__ get_ith_rtsi_brd_reg (int,struct comedi_device*) ; 
 scalar_t__ ni_lookup_route_register (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_ith_rtsi_brd_reg (int,scalar_t__,struct comedi_device*) ; 

__attribute__((used)) static int incr_rtsi_brd_src_use(int src, struct comedi_device *dev)
{
	struct ni_private *devpriv = dev->private;
	int first_available = -1;
	int err = -EINVAL;
	s8 reg;
	int i;

	/* first look for a mux that is already configured to provide src */
	for (i = 0; i < NUM_RTSI_SHARED_MUXS; ++i) {
		reg = ni_lookup_route_register(CR_CHAN(src), NI_RTSI_BRD(i),
					       &devpriv->routing_tables);

		if (reg < 0)
			continue; /* invalid route */

		if (!devpriv->rtsi_shared_mux_usage[i]) {
			if (first_available < 0)
				/* found the first unused, but usable mux */
				first_available = i;
		} else {
			/*
			 * we've seen at least one possible route, so change the
			 * final error to -EBUSY in case there are no muxes
			 * available.
			 */
			err = -EBUSY;

			if (get_ith_rtsi_brd_reg(i, dev) == reg) {
				/*
				 * we've found a mux that is already being used
				 * to provide the requested signal.  Reuse it.
				 */
				goto success;
			}
		}
	}

	if (first_available < 0)
		return err;

	/* we did not find a mux to reuse, but there is at least one usable */
	i = first_available;

success:
	++devpriv->rtsi_shared_mux_usage[i];
	set_ith_rtsi_brd_reg(i, reg, dev);
	return NI_RTSI_BRD(i);
}