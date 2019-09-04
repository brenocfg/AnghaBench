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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum sensors { ____Placeholder_sensors } sensors ;

/* Variables and functions */
 int ENOENT ; 
 char const* ERR_PTR (int) ; 
 int MAX_ATTR_LEN ; 
 char* convert_opal_attr_name (int,char*) ; 
 int get_sensor_index_attr (char const*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static const char *parse_opal_node_name(const char *node_name,
					enum sensors type, u32 *index)
{
	char attr_suffix[MAX_ATTR_LEN];
	const char *attr_name;
	int err;

	err = get_sensor_index_attr(node_name, index, attr_suffix);
	if (err)
		return ERR_PTR(err);

	attr_name = convert_opal_attr_name(type, attr_suffix);
	if (!attr_name)
		return ERR_PTR(-ENOENT);

	return attr_name;
}