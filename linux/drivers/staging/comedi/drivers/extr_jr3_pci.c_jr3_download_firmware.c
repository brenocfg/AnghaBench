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
typedef  int /*<<< orphan*/  u8 ;
struct comedi_device {int n_subdevices; } ;

/* Variables and functions */
 int jr3_check_firmware (struct comedi_device*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  jr3_write_firmware (struct comedi_device*,int,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int jr3_download_firmware(struct comedi_device *dev,
				 const u8 *data, size_t size,
				 unsigned long context)
{
	int subdev;
	int ret;

	/* verify IDM file format */
	ret = jr3_check_firmware(dev, data, size);
	if (ret)
		return ret;

	/* write firmware to each subdevice */
	for (subdev = 0; subdev < dev->n_subdevices; subdev++)
		jr3_write_firmware(dev, subdev, data, size);

	return 0;
}