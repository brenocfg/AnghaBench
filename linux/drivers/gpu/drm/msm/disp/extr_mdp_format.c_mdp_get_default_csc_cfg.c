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
struct csc_cfg {int dummy; } ;
typedef  enum csc_type { ____Placeholder_csc_type } csc_type ;

/* Variables and functions */
 int CSC_MAX ; 
 scalar_t__ WARN_ON (int) ; 
 struct csc_cfg* csc_convert ; 

struct csc_cfg *mdp_get_default_csc_cfg(enum csc_type type)
{
	if (WARN_ON(type >= CSC_MAX))
		return NULL;

	return &csc_convert[type];
}