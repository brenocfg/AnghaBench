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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pointerMode; } ;
struct aiptek {int diagnostic; TYPE_1__ curSetting; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  AIPTEK_DIAGNOSTIC_NA 131 
#define  AIPTEK_DIAGNOSTIC_SENDING_ABSOLUTE_IN_RELATIVE 130 
#define  AIPTEK_DIAGNOSTIC_SENDING_RELATIVE_IN_ABSOLUTE 129 
#define  AIPTEK_DIAGNOSTIC_TOOL_DISALLOWED 128 
 int /*<<< orphan*/  AIPTEK_POINTER_ONLY_MOUSE_MODE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct aiptek* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t show_tabletDiagnosticMessage(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct aiptek *aiptek = dev_get_drvdata(dev);
	char *retMsg;

	switch (aiptek->diagnostic) {
	case AIPTEK_DIAGNOSTIC_NA:
		retMsg = "no errors\n";
		break;

	case AIPTEK_DIAGNOSTIC_SENDING_RELATIVE_IN_ABSOLUTE:
		retMsg = "Error: receiving relative reports\n";
		break;

	case AIPTEK_DIAGNOSTIC_SENDING_ABSOLUTE_IN_RELATIVE:
		retMsg = "Error: receiving absolute reports\n";
		break;

	case AIPTEK_DIAGNOSTIC_TOOL_DISALLOWED:
		if (aiptek->curSetting.pointerMode ==
		    AIPTEK_POINTER_ONLY_MOUSE_MODE) {
			retMsg = "Error: receiving stylus reports\n";
		} else {
			retMsg = "Error: receiving mouse reports\n";
		}
		break;

	default:
		return 0;
	}
	return snprintf(buf, PAGE_SIZE, retMsg);
}