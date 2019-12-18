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
typedef  int u8 ;
struct edid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_for_each_detailed_block (int*,int /*<<< orphan*/ ,int**) ; 
 int /*<<< orphan*/  find_gtf2 ; 

__attribute__((used)) static int
drm_gtf2_k(struct edid *edid)
{
	u8 *r = NULL;
	drm_for_each_detailed_block((u8 *)edid, find_gtf2, &r);
	return r ? r[16] : 0;
}