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
typedef  int /*<<< orphan*/  vpd ;
struct cxl_afu {int dummy; } ;
struct cxl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxl_dump_debug_buffer (char*,int) ; 
 int cxl_guest_read_adapter_vpd (struct cxl*,char*,size_t) ; 
 int cxl_guest_read_afu_vpd (struct cxl_afu*,char*,size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int read_vpd(struct cxl *adapter, struct cxl_afu *afu)
{
	char vpd[256];
	int rc;
	size_t len = sizeof(vpd);

	memset(vpd, 0, len);

	if (adapter)
		rc = cxl_guest_read_adapter_vpd(adapter, vpd, len);
	else
		rc = cxl_guest_read_afu_vpd(afu, vpd, len);

	if (rc > 0) {
		cxl_dump_debug_buffer(vpd, rc);
		rc = 0;
	}
	return rc;
}