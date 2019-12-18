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
struct comedi_device {int dummy; } ;
struct comedi_devconfig {int /*<<< orphan*/ * options; } ;

/* Variables and functions */
 int amplc_dio200_common_attach (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int comedi_request_region (struct comedi_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dio200_attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	int ret;

	ret = comedi_request_region(dev, it->options[0], 0x20);
	if (ret)
		return ret;

	return amplc_dio200_common_attach(dev, it->options[1], 0);
}