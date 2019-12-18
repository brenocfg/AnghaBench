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
struct radio_isa_card {int dummy; } ;
struct gemtek {int muted; struct radio_isa_card isa; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct gemtek* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct radio_isa_card *gemtek_alloc(void)
{
	struct gemtek *gt = kzalloc(sizeof(*gt), GFP_KERNEL);

	if (gt)
		gt->muted = true;
	return gt ? &gt->isa : NULL;
}