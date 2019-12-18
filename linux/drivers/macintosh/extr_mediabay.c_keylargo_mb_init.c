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
struct media_bay_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEYLARGO_MBCR ; 
 int /*<<< orphan*/  KL_MBCR_MB0_ENABLE ; 
 int /*<<< orphan*/  MB_BIS (struct media_bay_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keylargo_mb_init(struct media_bay_info *bay)
{
	MB_BIS(bay, KEYLARGO_MBCR, KL_MBCR_MB0_ENABLE);
}