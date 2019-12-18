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
struct ni_private {int /*<<< orphan*/  routing_tables; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 int NI_RTSI_BRD (int) ; 
 int get_ith_rtsi_brd_reg (int,struct comedi_device*) ; 
 int ni_find_route_source (int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int get_rtsi_brd_src(int brd, struct comedi_device *dev)
{
	struct ni_private *devpriv = dev->private;
	int brd_index = brd;
	int reg;

	if (brd >= NI_RTSI_BRD(0))
		brd_index = brd - NI_RTSI_BRD(0);
	else
		brd = NI_RTSI_BRD(brd);
	/*
	 * And now:
	 * brd : device-global name
	 * brd_index : index number of RTSI_BRD mux
	 */

	reg = get_ith_rtsi_brd_reg(brd_index, dev);

	return ni_find_route_source(reg, brd, &devpriv->routing_tables);
}