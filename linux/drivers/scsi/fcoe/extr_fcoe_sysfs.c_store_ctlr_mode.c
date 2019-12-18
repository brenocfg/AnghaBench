#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fcoe_ctlr_device {int enabled; TYPE_1__* f; int /*<<< orphan*/  mode; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_fcoe_ctlr_mode ) (struct fcoe_ctlr_device*) ;} ;

/* Variables and functions */
 size_t EBUSY ; 
 size_t EINVAL ; 
 size_t ENOTSUPP ; 
#define  FCOE_CTLR_DISABLED 130 
#define  FCOE_CTLR_ENABLED 129 
#define  FCOE_CTLR_UNUSED 128 
 int FCOE_MAX_MODENAME_LEN ; 
 int /*<<< orphan*/  FIP_CONN_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  LIBFCOE_SYSFS_DBG (struct fcoe_ctlr_device*,char*,...) ; 
 struct fcoe_ctlr_device* dev_to_ctlr (struct device*) ; 
 int /*<<< orphan*/  fcoe_parse_mode (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  stub1 (struct fcoe_ctlr_device*) ; 

__attribute__((used)) static ssize_t store_ctlr_mode(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	struct fcoe_ctlr_device *ctlr = dev_to_ctlr(dev);
	char mode[FCOE_MAX_MODENAME_LEN + 1];

	if (count > FCOE_MAX_MODENAME_LEN)
		return -EINVAL;

	strncpy(mode, buf, count);

	if (mode[count - 1] == '\n')
		mode[count - 1] = '\0';
	else
		mode[count] = '\0';

	switch (ctlr->enabled) {
	case FCOE_CTLR_ENABLED:
		LIBFCOE_SYSFS_DBG(ctlr, "Cannot change mode when enabled.\n");
		return -EBUSY;
	case FCOE_CTLR_DISABLED:
		if (!ctlr->f->set_fcoe_ctlr_mode) {
			LIBFCOE_SYSFS_DBG(ctlr,
					  "Mode change not supported by LLD.\n");
			return -ENOTSUPP;
		}

		ctlr->mode = fcoe_parse_mode(mode);
		if (ctlr->mode == FIP_CONN_TYPE_UNKNOWN) {
			LIBFCOE_SYSFS_DBG(ctlr, "Unknown mode %s provided.\n",
					  buf);
			return -EINVAL;
		}

		ctlr->f->set_fcoe_ctlr_mode(ctlr);
		LIBFCOE_SYSFS_DBG(ctlr, "Mode changed to %s.\n", buf);

		return count;
	case FCOE_CTLR_UNUSED:
	default:
		LIBFCOE_SYSFS_DBG(ctlr, "Mode change not supported.\n");
		return -ENOTSUPP;
	};
}