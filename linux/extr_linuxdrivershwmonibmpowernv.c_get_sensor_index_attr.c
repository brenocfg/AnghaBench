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
typedef  int u32 ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_ATTR_LEN ; 
 int kstrtou32 (char*,int,int*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int get_sensor_index_attr(const char *name, u32 *index, char *attr)
{
	char *hash_pos = strchr(name, '#');
	char buf[8] = { 0 };
	char *dash_pos;
	u32 copy_len;
	int err;

	if (!hash_pos)
		return -EINVAL;

	dash_pos = strchr(hash_pos, '-');
	if (!dash_pos)
		return -EINVAL;

	copy_len = dash_pos - hash_pos - 1;
	if (copy_len >= sizeof(buf))
		return -EINVAL;

	strncpy(buf, hash_pos + 1, copy_len);

	err = kstrtou32(buf, 10, index);
	if (err)
		return err;

	strncpy(attr, dash_pos + 1, MAX_ATTR_LEN);

	return 0;
}