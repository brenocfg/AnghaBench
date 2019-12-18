#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct subchannel {int dummy; } ;
struct TYPE_2__ {int suspend; int prefetch; int inter; } ;
struct io_subchannel_private {TYPE_1__ options; } ;

/* Variables and functions */
 int DOIO_ALLOW_SUSPEND ; 
 int DOIO_DENY_PREFETCH ; 
 int DOIO_SUPPRESS_INTER ; 
 struct io_subchannel_private* to_io_private (struct subchannel*) ; 

int cio_set_options(struct subchannel *sch, int flags)
{
	struct io_subchannel_private *priv = to_io_private(sch);

	priv->options.suspend = (flags & DOIO_ALLOW_SUSPEND) != 0;
	priv->options.prefetch = (flags & DOIO_DENY_PREFETCH) != 0;
	priv->options.inter = (flags & DOIO_SUPPRESS_INTER) != 0;
	return 0;
}