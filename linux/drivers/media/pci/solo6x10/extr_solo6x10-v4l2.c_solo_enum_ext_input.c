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
struct v4l2_input {int index; int /*<<< orphan*/  name; } ;
struct solo_dev {int nr_chans; int nr_ext; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int solo_enum_ext_input(struct solo_dev *solo_dev,
			       struct v4l2_input *input)
{
	int ext = input->index - solo_dev->nr_chans;
	unsigned int nup, first;

	if (ext >= solo_dev->nr_ext)
		return -EINVAL;

	nup   = (ext == 4) ? 16 : 4;
	first = (ext & 3) << 2; /* first channel in the n-up */
	snprintf(input->name, sizeof(input->name),
		 "Multi %d-up (cameras %d-%d)",
		 nup, first + 1, first + nup);
	/* Possible outputs:
	 *  Multi 4-up (cameras 1-4)
	 *  Multi 4-up (cameras 5-8)
	 *  Multi 4-up (cameras 9-12)
	 *  Multi 4-up (cameras 13-16)
	 *  Multi 16-up (cameras 1-16)
	 */
	return 0;
}