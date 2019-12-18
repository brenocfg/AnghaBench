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
struct genwqe_dev {int softreset; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct genwqe_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t next_bitstream_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	int next_bitstream;
	struct genwqe_dev *cd = dev_get_drvdata(dev);

	switch ((cd->softreset & 0xc) >> 2) {
	case 0x2:
		next_bitstream =  0;
		break;
	case 0x3:
		next_bitstream =  1;
		break;
	default:
		next_bitstream = -1;
		break;		/* error */
	}
	return sprintf(buf, "%d\n", next_bitstream);
}