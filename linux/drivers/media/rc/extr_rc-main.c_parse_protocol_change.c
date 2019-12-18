#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct rc_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {char* name; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_1__* proto_names ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int parse_protocol_change(struct rc_dev *dev, u64 *protocols,
				 const char *buf)
{
	const char *tmp;
	unsigned count = 0;
	bool enable, disable;
	u64 mask;
	int i;

	while ((tmp = strsep((char **)&buf, " \n")) != NULL) {
		if (!*tmp)
			break;

		if (*tmp == '+') {
			enable = true;
			disable = false;
			tmp++;
		} else if (*tmp == '-') {
			enable = false;
			disable = true;
			tmp++;
		} else {
			enable = false;
			disable = false;
		}

		for (i = 0; i < ARRAY_SIZE(proto_names); i++) {
			if (!strcasecmp(tmp, proto_names[i].name)) {
				mask = proto_names[i].type;
				break;
			}
		}

		if (i == ARRAY_SIZE(proto_names)) {
			if (!strcasecmp(tmp, "lirc"))
				mask = 0;
			else {
				dev_dbg(&dev->dev, "Unknown protocol: '%s'\n",
					tmp);
				return -EINVAL;
			}
		}

		count++;

		if (enable)
			*protocols |= mask;
		else if (disable)
			*protocols &= ~mask;
		else
			*protocols = mask;
	}

	if (!count) {
		dev_dbg(&dev->dev, "Protocol not specified\n");
		return -EINVAL;
	}

	return count;
}