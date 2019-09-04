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
 int /*<<< orphan*/  lv1_panic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void ps3_exit(void)
{
	printf("ps3_exit\n");

	/* lv1_panic will shutdown the lpar. */

	lv1_panic(0); /* zero = do not reboot */
	while (1);
}