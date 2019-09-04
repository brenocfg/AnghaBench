#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  demod; } ;
struct sx8 {TYPE_1__ mci; } ;
struct mci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SX8_DEMOD_NONE ; 

__attribute__((used)) static int init(struct mci *mci)
{
	struct sx8 *state = (struct sx8 *)mci;

	state->mci.demod = SX8_DEMOD_NONE;
	return 0;
}