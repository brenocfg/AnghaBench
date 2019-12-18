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
struct hclge_desc {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int EIO ; 
 int HCLGE_VF_NUM_IN_FIRST_DESC ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static int hclge_update_desc_vfid(struct hclge_desc *desc, int vfid, bool clr)
{
#define HCLGE_VF_NUM_IN_FIRST_DESC 192

	unsigned int word_num;
	unsigned int bit_num;

	if (vfid > 255 || vfid < 0)
		return -EIO;

	if (vfid >= 0 && vfid < HCLGE_VF_NUM_IN_FIRST_DESC) {
		word_num = vfid / 32;
		bit_num  = vfid % 32;
		if (clr)
			desc[1].data[word_num] &= cpu_to_le32(~(1 << bit_num));
		else
			desc[1].data[word_num] |= cpu_to_le32(1 << bit_num);
	} else {
		word_num = (vfid - HCLGE_VF_NUM_IN_FIRST_DESC) / 32;
		bit_num  = vfid % 32;
		if (clr)
			desc[2].data[word_num] &= cpu_to_le32(~(1 << bit_num));
		else
			desc[2].data[word_num] |= cpu_to_le32(1 << bit_num);
	}

	return 0;
}