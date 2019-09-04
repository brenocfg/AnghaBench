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
typedef  scalar_t__ u16 ;
struct apple_key_translation {scalar_t__ from; } ;

/* Variables and functions */

__attribute__((used)) static const struct apple_key_translation *apple_find_translation(
		const struct apple_key_translation *table, u16 from)
{
	const struct apple_key_translation *trans;

	/* Look for the translation */
	for (trans = table; trans->from; trans++)
		if (trans->from == from)
			return trans;

	return NULL;
}