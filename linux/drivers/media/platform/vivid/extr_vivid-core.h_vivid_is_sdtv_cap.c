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
struct vivid_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ vivid_is_svid_cap (struct vivid_dev const*) ; 
 scalar_t__ vivid_is_tv_cap (struct vivid_dev const*) ; 

__attribute__((used)) static inline bool vivid_is_sdtv_cap(const struct vivid_dev *dev)
{
	return vivid_is_tv_cap(dev) || vivid_is_svid_cap(dev);
}