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
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int db2k_8255_cb(struct comedi_device *dev, int dir, int port, int data,
			unsigned long iobase)
{
	if (dir) {
		writew(data, dev->mmio + iobase + port * 2);
		return 0;
	}
	return readw(dev->mmio + iobase + port * 2);
}