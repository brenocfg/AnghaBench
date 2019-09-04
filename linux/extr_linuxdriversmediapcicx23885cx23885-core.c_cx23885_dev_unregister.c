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
struct cx23885_dev {size_t board; int /*<<< orphan*/  lmmio; int /*<<< orphan*/ * i2c_bus; int /*<<< orphan*/  ts2; int /*<<< orphan*/  ts1; int /*<<< orphan*/  refcount; int /*<<< orphan*/  pci; } ;
struct TYPE_2__ {scalar_t__ porta; scalar_t__ portb; scalar_t__ portc; } ;

/* Variables and functions */
 scalar_t__ CX23885_ANALOG_VIDEO ; 
 scalar_t__ CX23885_MPEG_DVB ; 
 scalar_t__ CX23885_MPEG_ENCODER ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx23885_417_unregister (struct cx23885_dev*) ; 
 TYPE_1__* cx23885_boards ; 
 int /*<<< orphan*/  cx23885_dvb_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx23885_i2c_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx23885_video_unregister (struct cx23885_dev*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cx23885_dev_unregister(struct cx23885_dev *dev)
{
	release_mem_region(pci_resource_start(dev->pci, 0),
			   pci_resource_len(dev->pci, 0));

	if (!atomic_dec_and_test(&dev->refcount))
		return;

	if (cx23885_boards[dev->board].porta == CX23885_ANALOG_VIDEO)
		cx23885_video_unregister(dev);

	if (cx23885_boards[dev->board].portb == CX23885_MPEG_DVB)
		cx23885_dvb_unregister(&dev->ts1);

	if (cx23885_boards[dev->board].portb == CX23885_MPEG_ENCODER)
		cx23885_417_unregister(dev);

	if (cx23885_boards[dev->board].portc == CX23885_MPEG_DVB)
		cx23885_dvb_unregister(&dev->ts2);

	if (cx23885_boards[dev->board].portc == CX23885_MPEG_ENCODER)
		cx23885_417_unregister(dev);

	cx23885_i2c_unregister(&dev->i2c_bus[2]);
	cx23885_i2c_unregister(&dev->i2c_bus[1]);
	cx23885_i2c_unregister(&dev->i2c_bus[0]);

	iounmap(dev->lmmio);
}