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

/* Variables and functions */

__attribute__((used)) static u8 svd_to_vic(u8 svd)
{
	/* 0-6 bit vic, 7th bit native mode indicator */
	if ((svd >= 1 &&  svd <= 64) || (svd >= 129 && svd <= 192))
		return svd & 127;

	return svd;
}