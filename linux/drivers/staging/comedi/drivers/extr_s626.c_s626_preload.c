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
typedef  int u32 ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ S626_LP_CNTR (unsigned int) ; 
 int /*<<< orphan*/  s626_debi_write (struct comedi_device*,scalar_t__,int) ; 

__attribute__((used)) static void s626_preload(struct comedi_device *dev,
			 unsigned int chan, u32 value)
{
	s626_debi_write(dev, S626_LP_CNTR(chan), value);
	s626_debi_write(dev, S626_LP_CNTR(chan) + 2, value >> 16);
}