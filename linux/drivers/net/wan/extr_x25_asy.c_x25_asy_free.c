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
struct x25_asy {int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; int /*<<< orphan*/ * xbuff; int /*<<< orphan*/ * rbuff; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLF_INUSE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void x25_asy_free(struct x25_asy *sl)
{
	/* Free all X.25 frame buffers. */
	kfree(sl->rbuff);
	sl->rbuff = NULL;
	kfree(sl->xbuff);
	sl->xbuff = NULL;

	if (!test_and_clear_bit(SLF_INUSE, &sl->flags))
		netdev_err(sl->dev, "x25_asy_free for already free unit\n");
}