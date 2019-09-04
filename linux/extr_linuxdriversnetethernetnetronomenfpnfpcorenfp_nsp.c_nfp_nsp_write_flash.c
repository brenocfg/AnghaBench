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
typedef  double u32 ;
struct nfp_nsp {int dummy; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPCODE_NSP_WRITE_FLASH ; 
 int __nfp_nsp_command_buf (struct nfp_nsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,double) ; 

int nfp_nsp_write_flash(struct nfp_nsp *state, const struct firmware *fw)
{
	/* The flash time is specified to take a maximum of 70s so we add an
	 * additional factor to this spec time.
	 */
	u32 timeout_sec = 2.5 * 70;

	return __nfp_nsp_command_buf(state, SPCODE_NSP_WRITE_FLASH, fw->size,
				     fw->data, fw->size, NULL, 0, timeout_sec);
}