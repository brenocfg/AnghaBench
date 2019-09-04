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
struct mci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mci_reset (struct mci*) ; 

__attribute__((used)) static int probe(struct mci *state)
{
	mci_reset(state);
	return 0;
}