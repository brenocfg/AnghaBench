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
struct dvb_frontend {TYPE_1__* dvb; } ;
struct cx88_core {int dummy; } ;
struct cx8802_dev {struct cx88_core* core; } ;
struct TYPE_2__ {struct cx8802_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MO_SRST_IO ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int cx24116_reset_device(struct dvb_frontend *fe)
{
	struct cx8802_dev *dev = fe->dvb->priv;
	struct cx88_core *core = dev->core;

	/* Reset the part */
	/* Put the cx24116 into reset */
	cx_write(MO_SRST_IO, 0);
	usleep_range(10000, 20000);
	/* Take the cx24116 out of reset */
	cx_write(MO_SRST_IO, 1);
	usleep_range(10000, 20000);

	return 0;
}