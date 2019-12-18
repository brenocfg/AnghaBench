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
struct dc_state {int dummy; } ;
struct dc {int dummy; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;

/* Variables and functions */
 int DC_FAIL_SURFACE_VALIDATE ; 
 int DC_OK ; 
 int /*<<< orphan*/  dce100_validate_surface_sets (struct dc_state*) ; 

enum dc_status dce100_validate_global(
		struct dc  *dc,
		struct dc_state *context)
{
	if (!dce100_validate_surface_sets(context))
		return DC_FAIL_SURFACE_VALIDATE;

	return DC_OK;
}