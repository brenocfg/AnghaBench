#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nr; struct e1000_opt_list* p; } ;
struct TYPE_5__ {unsigned int min; unsigned int max; } ;
struct TYPE_7__ {TYPE_2__ l; TYPE_1__ r; } ;
struct e1000_option {unsigned int def; int type; int /*<<< orphan*/  err; int /*<<< orphan*/  name; TYPE_3__ arg; } ;
struct e1000_opt_list {unsigned int i; char* str; } ;
struct e1000_adapter {TYPE_4__* pdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  OPTION_DISABLED 132 
#define  OPTION_ENABLED 131 
 unsigned int OPTION_UNSET ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,...) ; 
#define  enable_option 130 
#define  list_option 129 
#define  range_option 128 

__attribute__((used)) static int e1000_validate_option(unsigned int *value,
				 const struct e1000_option *opt,
				 struct e1000_adapter *adapter)
{
	if (*value == OPTION_UNSET) {
		*value = opt->def;
		return 0;
	}

	switch (opt->type) {
	case enable_option:
		switch (*value) {
		case OPTION_ENABLED:
			dev_info(&adapter->pdev->dev, "%s Enabled\n",
				 opt->name);
			return 0;
		case OPTION_DISABLED:
			dev_info(&adapter->pdev->dev, "%s Disabled\n",
				 opt->name);
			return 0;
		}
		break;
	case range_option:
		if (*value >= opt->arg.r.min && *value <= opt->arg.r.max) {
			dev_info(&adapter->pdev->dev, "%s set to %i\n",
				 opt->name, *value);
			return 0;
		}
		break;
	case list_option: {
		int i;
		struct e1000_opt_list *ent;

		for (i = 0; i < opt->arg.l.nr; i++) {
			ent = &opt->arg.l.p[i];
			if (*value == ent->i) {
				if (ent->str[0] != '\0')
					dev_info(&adapter->pdev->dev, "%s\n",
						 ent->str);
				return 0;
			}
		}
	}
		break;
	default:
		BUG();
	}

	dev_info(&adapter->pdev->dev, "Invalid %s value specified (%i) %s\n",
		 opt->name, *value, opt->err);
	*value = opt->def;
	return -1;
}