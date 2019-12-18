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
struct bnx2i_hba {int max_sqes; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct bnx2i_hba* bnx2i_dev_to_hba (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t bnx2i_show_sq_info(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	struct bnx2i_hba *hba = bnx2i_dev_to_hba(dev);

	return sprintf(buf, "0x%x\n", hba->max_sqes);
}