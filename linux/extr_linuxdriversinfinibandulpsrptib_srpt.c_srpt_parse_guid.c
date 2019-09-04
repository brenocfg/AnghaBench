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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  get_unaligned_be64 (int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int srpt_parse_guid(u64 *guid, const char *name)
{
	u16 w[4];
	int ret = -EINVAL;

	if (sscanf(name, "%hx:%hx:%hx:%hx", &w[0], &w[1], &w[2], &w[3]) != 4)
		goto out;
	*guid = get_unaligned_be64(w);
	ret = 0;
out:
	return ret;
}