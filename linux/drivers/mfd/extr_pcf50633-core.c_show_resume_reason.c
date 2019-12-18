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
struct pcf50633 {int* resume_reason; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct pcf50633* dev_get_drvdata (struct device*) ; 
 int sprintf (char*,char*,int,int,int,int,int) ; 

__attribute__((used)) static ssize_t show_resume_reason(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct pcf50633 *pcf = dev_get_drvdata(dev);
	int n;

	n = sprintf(buf, "%02x%02x%02x%02x%02x\n",
				pcf->resume_reason[0],
				pcf->resume_reason[1],
				pcf->resume_reason[2],
				pcf->resume_reason[3],
				pcf->resume_reason[4]);

	return n;
}