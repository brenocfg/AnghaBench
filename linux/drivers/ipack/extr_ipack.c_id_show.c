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
struct ipack_device {int id_format; unsigned int id_avail; int* id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  unsigned int ssize_t ;

/* Variables and functions */
 unsigned int EIO ; 
#define  IPACK_ID_VERSION_1 129 
#define  IPACK_ID_VERSION_2 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct ipack_device* to_ipack_dev (struct device*) ; 

__attribute__((used)) static ssize_t id_show(struct device *dev,
		       struct device_attribute *attr, char *buf)
{
	unsigned int i, c, l, s;
	struct ipack_device *idev = to_ipack_dev(dev);


	switch (idev->id_format) {
	case IPACK_ID_VERSION_1:
		l = 0x7; s = 1; break;
	case IPACK_ID_VERSION_2:
		l = 0xf; s = 2; break;
	default:
		return -EIO;
	}
	c = 0;
	for (i = 0; i < idev->id_avail; i++) {
		if (i > 0) {
			if ((i & l) == 0)
				buf[c++] = '\n';
			else if ((i & s) == 0)
				buf[c++] = ' ';
		}
		sprintf(&buf[c], "%02x", idev->id[i]);
		c += 2;
	}
	buf[c++] = '\n';
	return c;
}