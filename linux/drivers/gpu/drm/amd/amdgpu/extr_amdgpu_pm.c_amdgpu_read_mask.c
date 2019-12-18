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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  buf_cpy ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_MASK_BUF_MAX ; 
 int /*<<< orphan*/  EINVAL ; 
 int kstrtol (char*,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t min (size_t,int) ; 
 scalar_t__ strlen (char*) ; 
 char* strsep (char**,char const*) ; 

__attribute__((used)) static ssize_t amdgpu_read_mask(const char *buf, size_t count, uint32_t *mask)
{
	int ret;
	long level;
	char *sub_str = NULL;
	char *tmp;
	char buf_cpy[AMDGPU_MASK_BUF_MAX + 1];
	const char delimiter[3] = {' ', '\n', '\0'};
	size_t bytes;

	*mask = 0;

	bytes = min(count, sizeof(buf_cpy) - 1);
	memcpy(buf_cpy, buf, bytes);
	buf_cpy[bytes] = '\0';
	tmp = buf_cpy;
	while (tmp[0]) {
		sub_str = strsep(&tmp, delimiter);
		if (strlen(sub_str)) {
			ret = kstrtol(sub_str, 0, &level);
			if (ret)
				return -EINVAL;
			*mask |= 1 << level;
		} else
			break;
	}

	return 0;
}