#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  id ;
typedef  int /*<<< orphan*/  __le64 ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {scalar_t__ is_legacy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SENSOR_VALUE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_1__* scpi_info ; 
 int scpi_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int scpi_sensor_get_value(u16 sensor, u64 *val)
{
	__le16 id = cpu_to_le16(sensor);
	__le64 value;
	int ret;

	ret = scpi_send_message(CMD_SENSOR_VALUE, &id, sizeof(id),
				&value, sizeof(value));
	if (ret)
		return ret;

	if (scpi_info->is_legacy)
		/* only 32-bits supported, upper 32 bits can be junk */
		*val = le32_to_cpup((__le32 *)&value);
	else
		*val = le64_to_cpu(value);

	return 0;
}