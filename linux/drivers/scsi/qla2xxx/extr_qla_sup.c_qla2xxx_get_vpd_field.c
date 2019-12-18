#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct qla_hw_data {int* vpd; int vpd_size; } ;
struct TYPE_3__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla2xxx_is_vpd_valid (int*,int*) ; 
 int scnprintf (char*,size_t,char*,int,int*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (int*,char*,int /*<<< orphan*/ ) ; 

int
qla2xxx_get_vpd_field(scsi_qla_host_t *vha, char *key, char *str, size_t size)
{
	struct qla_hw_data *ha = vha->hw;
	uint8_t *pos = ha->vpd;
	uint8_t *end = pos + ha->vpd_size;
	int len = 0;

	if (!IS_FWI2_CAPABLE(ha) || !qla2xxx_is_vpd_valid(pos, end))
		return 0;

	while (pos < end && *pos != 0x78) {
		len = (*pos == 0x82) ? pos[1] : pos[2];

		if (!strncmp(pos, key, strlen(key)))
			break;

		if (*pos != 0x90 && *pos != 0x91)
			pos += len;

		pos += 3;
	}

	if (pos < end - len && *pos != 0x78)
		return scnprintf(str, size, "%.*s", len, pos + 3);

	return 0;
}