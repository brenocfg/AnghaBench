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
struct bgmac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGMAC_INT_MASK ; 
 int /*<<< orphan*/  bgmac_read (struct bgmac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgmac_write (struct bgmac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bgmac_chip_intrs_off(struct bgmac *bgmac)
{
	bgmac_write(bgmac, BGMAC_INT_MASK, 0);
	bgmac_read(bgmac, BGMAC_INT_MASK);
}