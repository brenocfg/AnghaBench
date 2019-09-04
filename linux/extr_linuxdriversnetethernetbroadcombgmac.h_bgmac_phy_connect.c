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
struct bgmac {int (* phy_connect ) (struct bgmac*) ;} ;

/* Variables and functions */
 int stub1 (struct bgmac*) ; 

__attribute__((used)) static inline int bgmac_phy_connect(struct bgmac *bgmac)
{
	return bgmac->phy_connect(bgmac);
}