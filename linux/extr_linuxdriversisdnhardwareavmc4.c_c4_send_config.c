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
typedef  int /*<<< orphan*/  val ;
typedef  int u_int ;
typedef  int /*<<< orphan*/ ******** u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int len; unsigned char* data; scalar_t__ user; } ;
typedef  TYPE_1__ capiloaddatapart ;
typedef  int /*<<< orphan*/  avmcard ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ **********,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **********,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *********,int /*<<< orphan*/ ,int) ; 
 int queue_sendconfig (int /*<<< orphan*/ *,int /*<<< orphan*/ *********) ; 
 int queue_sendconfigword (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int c4_send_config(avmcard *card, capiloaddatapart *config)
{
	u8 val[4];
	unsigned char *dp;
	u_int left;
	int retval;

	if ((retval = queue_sendconfigword(card, 1)) != 0)
		return retval;
	if ((retval = queue_sendconfigword(card, config->len)) != 0)
		return retval;

	dp = config->data;
	left = config->len;
	while (left >= sizeof(u32)) {
		if (config->user) {
			if (copy_from_user(val, dp, sizeof(val)))
				return -EFAULT;
		} else {
			memcpy(val, dp, sizeof(val));
		}
		if ((retval = queue_sendconfig(card, val)) != 0)
			return retval;
		left -= sizeof(val);
		dp += sizeof(val);
	}
	if (left) {
		memset(val, 0, sizeof(val));
		if (config->user) {
			if (copy_from_user(&val, dp, left))
				return -EFAULT;
		} else {
			memcpy(&val, dp, left);
		}
		if ((retval = queue_sendconfig(card, val)) != 0)
			return retval;
	}

	return 0;
}