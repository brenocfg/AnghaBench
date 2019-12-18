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
struct pnp_option {unsigned int flags; } ;

/* Variables and functions */
 unsigned int PNP_OPTION_PRIORITY_MASK ; 
 unsigned int PNP_OPTION_PRIORITY_SHIFT ; 

__attribute__((used)) static inline unsigned int pnp_option_priority(struct pnp_option *option)
{
	return (option->flags >> PNP_OPTION_PRIORITY_SHIFT) &
	    PNP_OPTION_PRIORITY_MASK;
}