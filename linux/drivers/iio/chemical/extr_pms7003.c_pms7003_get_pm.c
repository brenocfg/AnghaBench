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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  PMS7003_PM_MAX ; 
 int /*<<< orphan*/  PMS7003_PM_MIN ; 
 int /*<<< orphan*/  clamp_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_unaligned_be16 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static u16 pms7003_get_pm(const u8 *data)
{
	return clamp_val(get_unaligned_be16(data),
			 PMS7003_PM_MIN, PMS7003_PM_MAX);
}