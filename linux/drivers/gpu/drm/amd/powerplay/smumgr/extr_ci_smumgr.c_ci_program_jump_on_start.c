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
struct pp_hwmgr {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  ci_copy_bytes_to_smc (struct pp_hwmgr*,int,unsigned char const*,int,int) ; 

__attribute__((used)) static int ci_program_jump_on_start(struct pp_hwmgr *hwmgr)
{
	static const unsigned char data[4] = { 0xE0, 0x00, 0x80, 0x40 };

	ci_copy_bytes_to_smc(hwmgr, 0x0, data, 4, sizeof(data)+1);

	return 0;
}