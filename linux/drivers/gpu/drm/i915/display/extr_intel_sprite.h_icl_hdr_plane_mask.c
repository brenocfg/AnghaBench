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
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLANE_PRIMARY ; 
 int /*<<< orphan*/  PLANE_SPRITE0 ; 
 int /*<<< orphan*/  PLANE_SPRITE1 ; 

__attribute__((used)) static inline u8 icl_hdr_plane_mask(void)
{
	return BIT(PLANE_PRIMARY) |
		BIT(PLANE_SPRITE0) | BIT(PLANE_SPRITE1);
}