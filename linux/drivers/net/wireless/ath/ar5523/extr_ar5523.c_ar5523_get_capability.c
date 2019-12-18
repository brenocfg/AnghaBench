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
struct ar5523 {int dummy; } ;
typedef  int /*<<< orphan*/  cap_be ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AR5523_CMD_FLAG_MAGIC ; 
 int /*<<< orphan*/  WDCMSG_TARGET_GET_CAPABILITY ; 
 int ar5523_cmd_read (struct ar5523*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5523_err (struct ar5523*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ar5523_get_capability(struct ar5523 *ar, u32 cap, u32 *val)
{
	int error;
	__be32 cap_be, val_be;

	cap_be = cpu_to_be32(cap);
	error = ar5523_cmd_read(ar, WDCMSG_TARGET_GET_CAPABILITY, &cap_be,
				sizeof(cap_be), &val_be, sizeof(__be32),
				AR5523_CMD_FLAG_MAGIC);
	if (error != 0) {
		ar5523_err(ar, "could not read capability %u\n", cap);
		return error;
	}
	*val = be32_to_cpu(val_be);
	return error;
}