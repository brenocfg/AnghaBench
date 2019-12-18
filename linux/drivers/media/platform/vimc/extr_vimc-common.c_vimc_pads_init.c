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
typedef  unsigned int u16 ;
struct media_pad {unsigned int index; unsigned long flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct media_pad* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct media_pad* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 

struct media_pad *vimc_pads_init(u16 num_pads, const unsigned long *pads_flag)
{
	struct media_pad *pads;
	unsigned int i;

	/* Allocate memory for the pads */
	pads = kcalloc(num_pads, sizeof(*pads), GFP_KERNEL);
	if (!pads)
		return ERR_PTR(-ENOMEM);

	/* Initialize the pads */
	for (i = 0; i < num_pads; i++) {
		pads[i].index = i;
		pads[i].flags = pads_flag[i];
	}

	return pads;
}