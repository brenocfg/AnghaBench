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
typedef  size_t u16 ;
struct i40e_hw {int dummy; } ;
typedef  scalar_t__ i40e_status ;

/* Variables and functions */
 scalar_t__ i40e_read_nvm_word_srctl (struct i40e_hw*,size_t,size_t*) ; 

__attribute__((used)) static i40e_status i40e_read_nvm_buffer_srctl(struct i40e_hw *hw, u16 offset,
					      u16 *words, u16 *data)
{
	i40e_status ret_code = 0;
	u16 index, word;

	/* Loop thru the selected region */
	for (word = 0; word < *words; word++) {
		index = offset + word;
		ret_code = i40e_read_nvm_word_srctl(hw, index, &data[word]);
		if (ret_code)
			break;
	}

	/* Update the number of words read from the Shadow RAM */
	*words = word;

	return ret_code;
}