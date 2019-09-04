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

/* Variables and functions */
 int /*<<< orphan*/  sm4_key_lin_sub (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm4_t_non_lin_sub (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 sm4_key_sub(u32 x)
{
	return sm4_key_lin_sub(sm4_t_non_lin_sub(x));
}