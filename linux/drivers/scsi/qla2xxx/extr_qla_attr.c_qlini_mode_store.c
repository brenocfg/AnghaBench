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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int QLA2XXX_INI_MODE_DISABLED ; 
 int QLA2XXX_INI_MODE_DUAL ; 
 int QLA2XXX_INI_MODE_ENABLED ; 
 int QLA2XXX_INI_MODE_EXCLUSIVE ; 
 char const* QLA2XXX_INI_MODE_STR_DISABLED ; 
 char const* QLA2XXX_INI_MODE_STR_DUAL ; 
 char const* QLA2XXX_INI_MODE_STR_ENABLED ; 
 char const* QLA2XXX_INI_MODE_STR_EXCLUSIVE ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 int /*<<< orphan*/  qla_set_ini_mode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
qlini_mode_store(struct device *dev, struct device_attribute *attr,
    const char *buf, size_t count)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	int ini;

	if (!buf)
		return -EINVAL;

	if (strncasecmp(QLA2XXX_INI_MODE_STR_EXCLUSIVE, buf,
		strlen(QLA2XXX_INI_MODE_STR_EXCLUSIVE)) == 0)
		ini = QLA2XXX_INI_MODE_EXCLUSIVE;
	else if (strncasecmp(QLA2XXX_INI_MODE_STR_DISABLED, buf,
		strlen(QLA2XXX_INI_MODE_STR_DISABLED)) == 0)
		ini = QLA2XXX_INI_MODE_DISABLED;
	else if (strncasecmp(QLA2XXX_INI_MODE_STR_ENABLED, buf,
		  strlen(QLA2XXX_INI_MODE_STR_ENABLED)) == 0)
		ini = QLA2XXX_INI_MODE_ENABLED;
	else if (strncasecmp(QLA2XXX_INI_MODE_STR_DUAL, buf,
		strlen(QLA2XXX_INI_MODE_STR_DUAL)) == 0)
		ini = QLA2XXX_INI_MODE_DUAL;
	else
		return -EINVAL;

	qla_set_ini_mode(vha, ini);
	return strlen(buf);
}