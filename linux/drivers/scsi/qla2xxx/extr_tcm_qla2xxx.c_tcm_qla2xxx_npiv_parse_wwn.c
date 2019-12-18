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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int EINVAL ; 
 int tcm_qla2xxx_npiv_extract_wwn (char const*,scalar_t__*) ; 

__attribute__((used)) static int tcm_qla2xxx_npiv_parse_wwn(
	const char *name,
	size_t count,
	u64 *wwpn,
	u64 *wwnn)
{
	unsigned int cnt = count;
	int rc;

	*wwpn = 0;
	*wwnn = 0;

	/* count may include a LF at end of string */
	if (name[cnt-1] == '\n' || name[cnt-1] == 0)
		cnt--;

	/* validate we have enough characters for WWPN */
	if ((cnt != (16+1+16)) || (name[16] != ':'))
		return -EINVAL;

	rc = tcm_qla2xxx_npiv_extract_wwn(&name[0], wwpn);
	if (rc != 0)
		return rc;

	rc = tcm_qla2xxx_npiv_extract_wwn(&name[17], wwnn);
	if (rc != 0)
		return rc;

	return 0;
}