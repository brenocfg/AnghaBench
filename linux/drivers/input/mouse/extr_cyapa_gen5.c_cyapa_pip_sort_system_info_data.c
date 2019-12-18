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
struct cyapa {int dummy; } ;

/* Variables and functions */
 scalar_t__ VALID_CMD_RESP_HEADER (int /*<<< orphan*/ *,int) ; 

bool cyapa_pip_sort_system_info_data(struct cyapa *cyapa,
		u8 *buf, int len)
{
	/* Check the report id and command code */
	if (VALID_CMD_RESP_HEADER(buf, 0x02))
		return true;

	return false;
}