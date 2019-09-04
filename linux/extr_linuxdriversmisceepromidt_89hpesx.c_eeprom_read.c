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
typedef  int /*<<< orphan*/  u16 ;
struct kobject {int dummy; } ;
struct idt_89hpesx_dev {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 struct idt_89hpesx_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int idt_eeprom_read (struct idt_89hpesx_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobj_to_dev (struct kobject*) ; 

__attribute__((used)) static ssize_t eeprom_read(struct file *filp, struct kobject *kobj,
			   struct bin_attribute *attr,
			   char *buf, loff_t off, size_t count)
{
	struct idt_89hpesx_dev *pdev;
	int ret;

	/* Retrieve driver data */
	pdev = dev_get_drvdata(kobj_to_dev(kobj));

	/* Perform EEPROM read operation */
	ret = idt_eeprom_read(pdev, (u16)off, (u16)count, (u8 *)buf);
	return (ret != 0 ? ret : count);
}