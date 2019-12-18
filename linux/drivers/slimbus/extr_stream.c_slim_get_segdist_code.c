#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ratem; int segdist_code; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* segdist_codes ; 

__attribute__((used)) static int slim_get_segdist_code(int ratem)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(segdist_codes); i++) {
		if (segdist_codes[i].ratem == ratem)
			return segdist_codes[i].segdist_code;
	}

	return -EINVAL;
}