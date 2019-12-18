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
 int /*<<< orphan*/  NI_RGOUT0 ; 
 int get_rgout0_reg (struct comedi_device*) ; 
 int ni_find_route_source (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int get_rgout0_src(struct comedi_device *dev)
{
	struct ni_private *devpriv = dev->private;
	int reg = get_rgout0_reg(dev);

	return ni_find_route_source(reg, NI_RGOUT0, &devpriv->routing_tables);
}