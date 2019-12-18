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
typedef  int uint8_t ;
struct qla27xx_fwdt_template {int* driver_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  qla2x00_version_str ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*,int*,int*,int*,int*,int*) ; 

__attribute__((used)) static void
qla27xx_driver_info(struct qla27xx_fwdt_template *tmp)
{
	uint8_t v[] = { 0, 0, 0, 0, 0, 0 };

	WARN_ON_ONCE(sscanf(qla2x00_version_str,
			    "%hhu.%hhu.%hhu.%hhu.%hhu.%hhu",
			    v+0, v+1, v+2, v+3, v+4, v+5) != 6);

	tmp->driver_info[0] = v[3] << 24 | v[2] << 16 | v[1] << 8 | v[0];
	tmp->driver_info[1] = v[5] << 8 | v[4];
	tmp->driver_info[2] = 0x12345678;
}