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
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int* bcm2835_clk_claimed ; 
 TYPE_1__* clk_desc_array ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static bool bcm2835_clk_is_claimed(const char *name)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(clk_desc_array); i++) {
		const char *clk_name = *(const char **)(clk_desc_array[i].data);
		if (!strcmp(name, clk_name))
		    return bcm2835_clk_claimed[i];
	}

	return false;
}