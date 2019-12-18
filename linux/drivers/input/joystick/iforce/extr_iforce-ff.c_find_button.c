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
struct iforce {TYPE_1__* type; } ;
struct TYPE_2__ {short* btn; } ;

/* Variables and functions */

__attribute__((used)) static unsigned char find_button(struct iforce *iforce, signed short button)
{
	int i;

	for (i = 1; iforce->type->btn[i] >= 0; i++)
		if (iforce->type->btn[i] == button)
			return i + 1;
	return 0;
}