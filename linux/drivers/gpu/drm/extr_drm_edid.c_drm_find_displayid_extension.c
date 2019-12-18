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
typedef  int /*<<< orphan*/  u8 ;
struct edid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYID_EXT ; 
 int /*<<< orphan*/ * drm_find_edid_extension (struct edid const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 *drm_find_displayid_extension(const struct edid *edid)
{
	return drm_find_edid_extension(edid, DISPLAYID_EXT);
}