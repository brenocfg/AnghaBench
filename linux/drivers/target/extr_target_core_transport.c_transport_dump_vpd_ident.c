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
struct t10_vpd {int device_identifier_code_set; char* device_identifier; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EINVAL ; 
 int VPD_TMP_BUF_SIZE ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned char*) ; 
 int /*<<< orphan*/  snprintf (unsigned char*,int,char*,char*) ; 
 int /*<<< orphan*/  sprintf (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (unsigned char*,unsigned char*,int) ; 

int transport_dump_vpd_ident(
	struct t10_vpd *vpd,
	unsigned char *p_buf,
	int p_buf_len)
{
	unsigned char buf[VPD_TMP_BUF_SIZE];
	int ret = 0;

	memset(buf, 0, VPD_TMP_BUF_SIZE);

	switch (vpd->device_identifier_code_set) {
	case 0x01: /* Binary */
		snprintf(buf, sizeof(buf),
			"T10 VPD Binary Device Identifier: %s\n",
			&vpd->device_identifier[0]);
		break;
	case 0x02: /* ASCII */
		snprintf(buf, sizeof(buf),
			"T10 VPD ASCII Device Identifier: %s\n",
			&vpd->device_identifier[0]);
		break;
	case 0x03: /* UTF-8 */
		snprintf(buf, sizeof(buf),
			"T10 VPD UTF-8 Device Identifier: %s\n",
			&vpd->device_identifier[0]);
		break;
	default:
		sprintf(buf, "T10 VPD Device Identifier encoding unsupported:"
			" 0x%02x", vpd->device_identifier_code_set);
		ret = -EINVAL;
		break;
	}

	if (p_buf)
		strncpy(p_buf, buf, p_buf_len);
	else
		pr_debug("%s", buf);

	return ret;
}