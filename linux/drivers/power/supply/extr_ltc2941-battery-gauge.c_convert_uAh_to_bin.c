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
struct ltc294x_info {int Qlsb; } ;

/* Variables and functions */
 int LTC294X_MAX_VALUE ; 

__attribute__((used)) static inline int convert_uAh_to_bin(
	const struct ltc294x_info *info, int uAh)
{
	int Q;

	Q = (uAh * 100) / (info->Qlsb/10);
	return (Q < LTC294X_MAX_VALUE) ? Q : LTC294X_MAX_VALUE;
}