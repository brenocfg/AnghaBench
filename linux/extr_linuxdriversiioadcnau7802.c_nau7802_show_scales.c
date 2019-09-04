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
struct nau7802_state {int /*<<< orphan*/ * scale_avail; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 struct nau7802_state* iio_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t nau7802_show_scales(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct nau7802_state *st = iio_priv(dev_to_iio_dev(dev));
	int i, len = 0;

	for (i = 0; i < ARRAY_SIZE(st->scale_avail); i++)
		len += scnprintf(buf + len, PAGE_SIZE - len, "0.%09d ",
				 st->scale_avail[i]);

	buf[len-1] = '\n';

	return len;
}