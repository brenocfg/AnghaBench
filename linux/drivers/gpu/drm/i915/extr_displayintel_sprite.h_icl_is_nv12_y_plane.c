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
typedef  enum plane_id { ____Placeholder_plane_id } plane_id ;

/* Variables and functions */
 int PLANE_SPRITE4 ; 
 int PLANE_SPRITE5 ; 

__attribute__((used)) static inline bool icl_is_nv12_y_plane(enum plane_id id)
{
	/* Don't need to do a gen check, these planes are only available on gen11 */
	if (id == PLANE_SPRITE4 || id == PLANE_SPRITE5)
		return true;

	return false;
}