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

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*) ; 
 int /*<<< orphan*/  TAPE_DBF_AREA ; 
 int ccw_driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_register (char*,int,int,int) ; 
 int /*<<< orphan*/  debug_register_view (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_set_level (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debug_sprintf_view ; 
 int /*<<< orphan*/  tape_34xx_driver ; 

__attribute__((used)) static int
tape_34xx_init (void)
{
	int rc;

	TAPE_DBF_AREA = debug_register ( "tape_34xx", 2, 2, 4*sizeof(long));
	debug_register_view(TAPE_DBF_AREA, &debug_sprintf_view);
#ifdef DBF_LIKE_HELL
	debug_set_level(TAPE_DBF_AREA, 6);
#endif

	DBF_EVENT(3, "34xx init\n");
	/* Register driver for 3480/3490 tapes. */
	rc = ccw_driver_register(&tape_34xx_driver);
	if (rc)
		DBF_EVENT(3, "34xx init failed\n");
	else
		DBF_EVENT(3, "34xx registered\n");
	return rc;
}