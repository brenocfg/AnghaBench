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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ HOST1X_CLASS_GR2D ; 
 scalar_t__ HOST1X_CLASS_GR2D_SB ; 

__attribute__((used)) static int gr2d_is_valid_class(u32 class)
{
	return (class == HOST1X_CLASS_GR2D ||
		class == HOST1X_CLASS_GR2D_SB);
}