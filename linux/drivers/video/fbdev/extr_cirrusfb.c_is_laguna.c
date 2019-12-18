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
struct cirrusfb_info {scalar_t__ btype; } ;

/* Variables and functions */
 scalar_t__ BT_LAGUNA ; 
 scalar_t__ BT_LAGUNAB ; 

__attribute__((used)) static inline int is_laguna(const struct cirrusfb_info *cinfo)
{
	return cinfo->btype == BT_LAGUNA || cinfo->btype == BT_LAGUNAB;
}