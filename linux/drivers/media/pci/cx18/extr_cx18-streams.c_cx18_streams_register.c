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
struct cx18 {int dummy; } ;

/* Variables and functions */
 int CX18_MAX_STREAMS ; 
 int cx18_reg_dev (struct cx18*,int) ; 
 int /*<<< orphan*/  cx18_streams_cleanup (struct cx18*,int) ; 

int cx18_streams_register(struct cx18 *cx)
{
	int type;
	int err;
	int ret = 0;

	/* Register V4L2 devices */
	for (type = 0; type < CX18_MAX_STREAMS; type++) {
		err = cx18_reg_dev(cx, type);
		if (err && ret == 0)
			ret = err;
	}

	if (ret == 0)
		return 0;

	/* One or more streams could not be initialized. Clean 'em all up. */
	cx18_streams_cleanup(cx, 1);
	return ret;
}