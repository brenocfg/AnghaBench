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
struct ib_uverbs_file {int uverbs_cmd_mask; int uverbs_ex_cmd_mask; } ;

/* Variables and functions */
 int BIT_ULL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool verify_command_mask(struct ib_uverbs_file *ufile, u32 command,
				bool extended)
{
	if (!extended)
		return ufile->uverbs_cmd_mask & BIT_ULL(command);

	return ufile->uverbs_ex_cmd_mask & BIT_ULL(command);
}