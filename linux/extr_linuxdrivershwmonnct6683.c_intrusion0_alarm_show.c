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
typedef  int u8 ;
struct nct6683_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/  sioreg; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int NCT6683_CR_CASEOPEN_MASK ; 
 int /*<<< orphan*/  NCT6683_LD_ACPI ; 
 int /*<<< orphan*/  NCT6683_REG_CR_CASEOPEN ; 
 struct nct6683_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 
 int superio_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_exit (int /*<<< orphan*/ ) ; 
 int superio_inb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
intrusion0_alarm_show(struct device *dev, struct device_attribute *attr,
		      char *buf)
{
	struct nct6683_data *data = dev_get_drvdata(dev);
	int ret;
	u8 reg;

	mutex_lock(&data->update_lock);

	ret = superio_enter(data->sioreg);
	if (ret)
		goto error;
	superio_select(data->sioreg, NCT6683_LD_ACPI);
	reg = superio_inb(data->sioreg, NCT6683_REG_CR_CASEOPEN);
	superio_exit(data->sioreg);

	mutex_unlock(&data->update_lock);

	return sprintf(buf, "%u\n", !(reg & NCT6683_CR_CASEOPEN_MASK));

error:
	mutex_unlock(&data->update_lock);
	return ret;
}