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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 int APD_BIT ; 
 scalar_t__ CONFIG_REG ; 
 int DPD_BIT ; 
 int /*<<< orphan*/  a2150_free_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  comedi_legacy_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static void a2150_detach(struct comedi_device *dev)
{
	if (dev->iobase)
		outw(APD_BIT | DPD_BIT, dev->iobase + CONFIG_REG);
	a2150_free_dma(dev);
	comedi_legacy_detach(dev);
}