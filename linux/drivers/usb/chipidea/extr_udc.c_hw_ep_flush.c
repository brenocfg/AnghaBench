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
struct ci_hdrc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  OP_ENDPTFLUSH ; 
 int /*<<< orphan*/  OP_ENDPTSTAT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int hw_ep_bit (int,int) ; 
 scalar_t__ hw_read (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_write (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_ep_flush(struct ci_hdrc *ci, int num, int dir)
{
	int n = hw_ep_bit(num, dir);

	do {
		/* flush any pending transfer */
		hw_write(ci, OP_ENDPTFLUSH, ~0, BIT(n));
		while (hw_read(ci, OP_ENDPTFLUSH, BIT(n)))
			cpu_relax();
	} while (hw_read(ci, OP_ENDPTSTAT, BIT(n)));

	return 0;
}