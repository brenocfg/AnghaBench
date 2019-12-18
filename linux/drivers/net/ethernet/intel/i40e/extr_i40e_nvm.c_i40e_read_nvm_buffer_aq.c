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
typedef  scalar_t__ u16 ;
struct i40e_hw {int dummy; } ;
typedef  scalar_t__ i40e_status ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ I40E_SR_SECTOR_SIZE_IN_WORDS ; 
 scalar_t__ i40e_read_nvm_aq (struct i40e_hw*,int,scalar_t__,scalar_t__,scalar_t__*,int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static i40e_status i40e_read_nvm_buffer_aq(struct i40e_hw *hw, u16 offset,
					   u16 *words, u16 *data)
{
	i40e_status ret_code;
	u16 read_size;
	bool last_cmd = false;
	u16 words_read = 0;
	u16 i = 0;

	do {
		/* Calculate number of bytes we should read in this step.
		 * FVL AQ do not allow to read more than one page at a time or
		 * to cross page boundaries.
		 */
		if (offset % I40E_SR_SECTOR_SIZE_IN_WORDS)
			read_size = min(*words,
					(u16)(I40E_SR_SECTOR_SIZE_IN_WORDS -
				      (offset % I40E_SR_SECTOR_SIZE_IN_WORDS)));
		else
			read_size = min((*words - words_read),
					I40E_SR_SECTOR_SIZE_IN_WORDS);

		/* Check if this is last command, if so set proper flag */
		if ((words_read + read_size) >= *words)
			last_cmd = true;

		ret_code = i40e_read_nvm_aq(hw, 0x0, offset, read_size,
					    data + words_read, last_cmd);
		if (ret_code)
			goto read_nvm_buffer_aq_exit;

		/* Increment counter for words already read and move offset to
		 * new read location
		 */
		words_read += read_size;
		offset += read_size;
	} while (words_read < *words);

	for (i = 0; i < *words; i++)
		data[i] = le16_to_cpu(((__le16 *)data)[i]);

read_nvm_buffer_aq_exit:
	*words = words_read;
	return ret_code;
}