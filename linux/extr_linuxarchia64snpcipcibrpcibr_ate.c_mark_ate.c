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
typedef  int /*<<< orphan*/  u64 ;
struct ate_resource {int /*<<< orphan*/ * ate; } ;

/* Variables and functions */

__attribute__((used)) static void mark_ate(struct ate_resource *ate_resource, int start, int number,
		     u64 value)
{
	u64 *ate = ate_resource->ate;
	int index;
	int length = 0;

	for (index = start; length < number; index++, length++)
		ate[index] = value;
}