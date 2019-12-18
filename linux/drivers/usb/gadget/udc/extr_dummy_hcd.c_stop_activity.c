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
struct dummy {int /*<<< orphan*/ * ep; scalar_t__ address; } ;

/* Variables and functions */
 int DUMMY_ENDPOINTS ; 
 int /*<<< orphan*/  nuke (struct dummy*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stop_activity(struct dummy *dum)
{
	int i;

	/* prevent any more requests */
	dum->address = 0;

	/* The timer is left running so that outstanding URBs can fail */

	/* nuke any pending requests first, so driver i/o is quiesced */
	for (i = 0; i < DUMMY_ENDPOINTS; ++i)
		nuke(dum, &dum->ep[i]);

	/* driver now does any non-usb quiescing necessary */
}