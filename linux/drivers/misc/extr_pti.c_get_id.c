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
typedef  int u8 ;
struct pti_masterchannel {int master; int channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct pti_masterchannel*) ; 
 struct pti_masterchannel* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pti_control_frame_built_and_sent (struct pti_masterchannel*,char const*) ; 

__attribute__((used)) static struct pti_masterchannel *get_id(u8 *id_array,
					int max_ids,
					int base_id,
					const char *thread_name)
{
	struct pti_masterchannel *mc;
	int i, j, mask;

	mc = kmalloc(sizeof(struct pti_masterchannel), GFP_KERNEL);
	if (mc == NULL)
		return NULL;

	/* look for a byte with a free bit */
	for (i = 0; i < max_ids; i++)
		if (id_array[i] != 0xff)
			break;
	if (i == max_ids) {
		kfree(mc);
		return NULL;
	}
	/* find the bit in the 128 possible channel opportunities */
	mask = 0x80;
	for (j = 0; j < 8; j++) {
		if ((id_array[i] & mask) == 0)
			break;
		mask >>= 1;
	}

	/* grab it */
	id_array[i] |= mask;
	mc->master  = base_id;
	mc->channel = ((i & 0xf)<<3) + j;
	/* write new master Id / channel Id allocation to channel control */
	pti_control_frame_built_and_sent(mc, thread_name);
	return mc;
}