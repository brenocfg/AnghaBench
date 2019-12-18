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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cxlflash_cfg {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 int /*<<< orphan*/  cxlflash_show_port_status (int,struct cxlflash_cfg*,char*) ; 
 struct cxlflash_cfg* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t port3_show(struct device *dev,
			  struct device_attribute *attr,
			  char *buf)
{
	struct cxlflash_cfg *cfg = shost_priv(class_to_shost(dev));

	return cxlflash_show_port_status(3, cfg, buf);
}