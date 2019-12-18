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
struct ni_private {int /*<<< orphan*/  counter_dev; int /*<<< orphan*/  routing_tables; } ;
struct comedi_device {struct ni_private* private; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_INPUT ; 
 int /*<<< orphan*/  CR_CHAN (unsigned int) ; 
 int EINVAL ; 
 unsigned int NI_CtrOut (int) ; 
 int /*<<< orphan*/  NI_PFI_OUTPUT_PFI_DEFAULT ; 
 scalar_t__ NI_RTSI_OUTPUT_RGOUT0 ; 
 unsigned int TRIGGER_LINE (int /*<<< orphan*/ ) ; 
 scalar_t__ channel_is_ctr (unsigned int) ; 
 scalar_t__ channel_is_pfi (unsigned int) ; 
 scalar_t__ channel_is_rtsi (unsigned int) ; 
 int decr_rgout0_src_use (unsigned int,struct comedi_device*) ; 
 int /*<<< orphan*/  decr_rtsi_brd_src_use (unsigned int,int,struct comedi_device*) ; 
 scalar_t__* default_rtsi_routing ; 
 unsigned int get_output_select_source (unsigned int,struct comedi_device*) ; 
 scalar_t__ ni_disable_gout_routing (unsigned int,struct comedi_device*) ; 
 int ni_find_route_source (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ni_get_rtsi_routing (struct comedi_device*,unsigned int) ; 
 scalar_t__ ni_route_to_register (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ ni_rtsi_route_requires_mux (scalar_t__) ; 
 int /*<<< orphan*/  ni_set_pfi_direction (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_set_pfi_routing (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_set_rtsi_direction (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_set_rtsi_routing (struct comedi_device*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  ni_tio_unset_routing (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int disconnect_route(unsigned int src, unsigned int dest,
			    struct comedi_device *dev)
{
	struct ni_private *devpriv = dev->private;
	s8 reg = ni_route_to_register(CR_CHAN(src), dest,
				      &devpriv->routing_tables);

	if (reg < 0)
		/* route is not valid */
		return -EINVAL;
	if (get_output_select_source(dest, dev) != src)
		/* cannot disconnect something not connected */
		return -EINVAL;

	/* The route is valid and is connected.  Now disconnect... */
	if (channel_is_pfi(dest)) {
		/* set the pfi to high impedance, and disconnect */
		ni_set_pfi_direction(dev, dest, COMEDI_INPUT);
		ni_set_pfi_routing(dev, dest, NI_PFI_OUTPUT_PFI_DEFAULT);
	} else if (channel_is_rtsi(dest)) {
		if (reg == NI_RTSI_OUTPUT_RGOUT0) {
			int ret = decr_rgout0_src_use(src, dev);

			if (ret < 0)
				return ret;
		} else if (ni_rtsi_route_requires_mux(reg)) {
			/* find which RTSI_BRD line is source for rtsi pin */
			int brd = ni_find_route_source(
				ni_get_rtsi_routing(dev, dest), dest,
				&devpriv->routing_tables);

			if (brd < 0)
				return brd;

			/* decrement/disconnect RTSI_BRD line from source */
			decr_rtsi_brd_src_use(src, brd, dev);
		}

		/* set rtsi output selector to default state */
		reg = default_rtsi_routing[dest - TRIGGER_LINE(0)];
		ni_set_rtsi_direction(dev, dest, COMEDI_INPUT);
		ni_set_rtsi_routing(dev, dest, reg);
	} else if (dest >= NI_CtrOut(0) && dest <= NI_CtrOut(-1)) {
		/*
		 * not handled by ni_tio.  Only available for GPFO registers in
		 * e/m series.
		 */
		dest -= NI_CtrOut(0);
		if (dest > 1)
			/* there are only two g_out outputs. */
			return -EINVAL;
		reg = ni_disable_gout_routing(dest, dev);
	} else if (channel_is_ctr(dest)) {
		ni_tio_unset_routing(devpriv->counter_dev, dest);
	} else {
		return -EINVAL;
	}
	return 0;
}