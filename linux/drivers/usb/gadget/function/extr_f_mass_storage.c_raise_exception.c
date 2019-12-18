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
struct fsg_common {int dummy; } ;
typedef  enum fsg_state { ____Placeholder_fsg_state } fsg_state ;

/* Variables and functions */
 int /*<<< orphan*/  __raise_exception (struct fsg_common*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raise_exception(struct fsg_common *common, enum fsg_state new_state)
{
	__raise_exception(common, new_state, NULL);
}