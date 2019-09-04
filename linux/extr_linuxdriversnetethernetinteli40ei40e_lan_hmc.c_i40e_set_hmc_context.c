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
struct i40e_context_ele {scalar_t__ width; int size_of; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_write_byte (int /*<<< orphan*/ *,struct i40e_context_ele*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_write_dword (int /*<<< orphan*/ *,struct i40e_context_ele*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_write_qword (int /*<<< orphan*/ *,struct i40e_context_ele*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_write_word (int /*<<< orphan*/ *,struct i40e_context_ele*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static i40e_status i40e_set_hmc_context(u8 *context_bytes,
					struct i40e_context_ele *ce_info,
					u8 *dest)
{
	int f;

	for (f = 0; ce_info[f].width != 0; f++) {

		/* we have to deal with each element of the HMC using the
		 * correct size so that we are correct regardless of the
		 * endianness of the machine
		 */
		switch (ce_info[f].size_of) {
		case 1:
			i40e_write_byte(context_bytes, &ce_info[f], dest);
			break;
		case 2:
			i40e_write_word(context_bytes, &ce_info[f], dest);
			break;
		case 4:
			i40e_write_dword(context_bytes, &ce_info[f], dest);
			break;
		case 8:
			i40e_write_qword(context_bytes, &ce_info[f], dest);
			break;
		}
	}

	return 0;
}