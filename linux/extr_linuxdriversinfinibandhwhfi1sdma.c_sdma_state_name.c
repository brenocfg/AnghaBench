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
typedef  enum sdma_states { ____Placeholder_sdma_states } sdma_states ;

/* Variables and functions */
 char const** sdma_state_names ; 

__attribute__((used)) static const char *sdma_state_name(enum sdma_states state)
{
	return sdma_state_names[state];
}