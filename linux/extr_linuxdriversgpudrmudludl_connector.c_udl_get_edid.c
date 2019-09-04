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
struct udl_device {int dummy; } ;
struct edid {int extensions; } ;

/* Variables and functions */
 int EDID_LENGTH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memchr_inv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ udl_get_edid_block (struct udl_device*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool udl_get_edid(struct udl_device *udl, u8 **result_buff,
			 int *result_buff_size)
{
	int i, extensions;
	u8 *block_buff = NULL, *buff_ptr;

	block_buff = kmalloc(EDID_LENGTH, GFP_KERNEL);
	if (block_buff == NULL)
		return false;

	if (udl_get_edid_block(udl, 0, block_buff) &&
	    memchr_inv(block_buff, 0, EDID_LENGTH)) {
		extensions = ((struct edid *)block_buff)->extensions;
		if (extensions > 0) {
			/* we have to read all extensions one by one */
			*result_buff_size = EDID_LENGTH * (extensions + 1);
			*result_buff = kmalloc(*result_buff_size, GFP_KERNEL);
			buff_ptr = *result_buff;
			if (buff_ptr == NULL) {
				kfree(block_buff);
				return false;
			}
			memcpy(buff_ptr, block_buff, EDID_LENGTH);
			kfree(block_buff);
			buff_ptr += EDID_LENGTH;
			for (i = 1; i < extensions; ++i) {
				if (udl_get_edid_block(udl, i, buff_ptr)) {
					buff_ptr += EDID_LENGTH;
				} else {
					kfree(*result_buff);
					*result_buff = NULL;
					return false;
				}
			}
			return true;
		}
		/* we have only base edid block */
		*result_buff = block_buff;
		*result_buff_size = EDID_LENGTH;
		return true;
	}

	kfree(block_buff);

	return false;
}