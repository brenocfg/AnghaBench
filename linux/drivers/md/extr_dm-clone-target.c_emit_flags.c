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
struct clone {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMEMIT (char*,...) ; 
 int /*<<< orphan*/  DM_CLONE_DISCARD_PASSDOWN ; 
 int /*<<< orphan*/  DM_CLONE_HYDRATION_ENABLED ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void emit_flags(struct clone *clone, char *result, unsigned int maxlen,
		       ssize_t *sz_ptr)
{
	ssize_t sz = *sz_ptr;
	unsigned int count;

	count = !test_bit(DM_CLONE_HYDRATION_ENABLED, &clone->flags);
	count += !test_bit(DM_CLONE_DISCARD_PASSDOWN, &clone->flags);

	DMEMIT("%u ", count);

	if (!test_bit(DM_CLONE_HYDRATION_ENABLED, &clone->flags))
		DMEMIT("no_hydration ");

	if (!test_bit(DM_CLONE_DISCARD_PASSDOWN, &clone->flags))
		DMEMIT("no_discard_passdown ");

	*sz_ptr = sz;
}