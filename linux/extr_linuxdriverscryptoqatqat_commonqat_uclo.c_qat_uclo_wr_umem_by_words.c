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
struct icp_qat_fw_loader_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned char*,int) ; 
 int /*<<< orphan*/  qat_hal_wr_umem (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ,int,unsigned int*) ; 

__attribute__((used)) static void qat_uclo_wr_umem_by_words(struct icp_qat_fw_loader_handle *handle,
				      unsigned char ae, unsigned int addr,
				      unsigned int *val,
				      unsigned int num_in_bytes)
{
	unsigned int outval;
	unsigned char *ptr = (unsigned char *)val;

	addr >>= 0x2; /* convert to uword address */

	while (num_in_bytes) {
		memcpy(&outval, ptr, 4);
		qat_hal_wr_umem(handle, ae, addr++, 1, &outval);
		num_in_bytes -= 4;
		ptr += 4;
	}
}