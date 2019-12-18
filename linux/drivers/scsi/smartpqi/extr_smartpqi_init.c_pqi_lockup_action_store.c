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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  action_name_buffer ;
struct TYPE_3__ {int /*<<< orphan*/  action; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  pqi_lockup_action ; 
 TYPE_1__* pqi_lockup_actions ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 char* strstrip (char*) ; 

__attribute__((used)) static ssize_t pqi_lockup_action_store(struct device *dev,
	struct device_attribute *attr, const char *buffer, size_t count)
{
	unsigned int i;
	char *action_name;
	char action_name_buffer[32];

	strlcpy(action_name_buffer, buffer, sizeof(action_name_buffer));
	action_name = strstrip(action_name_buffer);

	for (i = 0; i < ARRAY_SIZE(pqi_lockup_actions); i++) {
		if (strcmp(action_name, pqi_lockup_actions[i].name) == 0) {
			pqi_lockup_action = pqi_lockup_actions[i].action;
			return count;
		}
	}

	return -EINVAL;
}