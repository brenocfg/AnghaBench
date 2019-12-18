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
struct macb {int caps; } ;

/* Variables and functions */
 int MACB_CAPS_GEM_HAS_PTP ; 

__attribute__((used)) static inline bool gem_has_ptp(struct macb *bp)
{
	return !!(bp->caps & MACB_CAPS_GEM_HAS_PTP);
}