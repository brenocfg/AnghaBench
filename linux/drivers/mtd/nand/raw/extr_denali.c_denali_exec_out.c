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
typedef  int /*<<< orphan*/  u32 ;
struct denali_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  denali_exec_out16 (struct denali_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  denali_exec_out8 (struct denali_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void denali_exec_out(struct denali_controller *denali, u32 type,
			    const u8 *buf, unsigned int len, bool width16)
{
	if (width16)
		denali_exec_out16(denali, type, buf, len);
	else
		denali_exec_out8(denali, type, buf, len);
}