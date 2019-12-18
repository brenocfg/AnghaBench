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
struct vmlogrdr_priv_t {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct vmlogrdr_priv_t* dev_get_drvdata (struct device*) ; 
 size_t vmlogrdr_recording (struct vmlogrdr_priv_t*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t vmlogrdr_recording_store(struct device * dev,
					struct device_attribute *attr,
					const char * buf, size_t count)
{
	struct vmlogrdr_priv_t *priv = dev_get_drvdata(dev);
	ssize_t ret;

	switch (buf[0]) {
	case '0':
		ret = vmlogrdr_recording(priv,0,0);
		break;
	case '1':
		ret = vmlogrdr_recording(priv,1,0);
		break;
	default:
		ret = -EINVAL;
	}
	if (ret)
		return ret;
	else
		return count;

}