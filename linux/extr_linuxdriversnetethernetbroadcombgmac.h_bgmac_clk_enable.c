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
typedef  int /*<<< orphan*/  u32 ;
struct bgmac {int /*<<< orphan*/  (* clk_enable ) (struct bgmac*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct bgmac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bgmac_clk_enable(struct bgmac *bgmac, u32 flags)
{
	bgmac->clk_enable(bgmac, flags);
}