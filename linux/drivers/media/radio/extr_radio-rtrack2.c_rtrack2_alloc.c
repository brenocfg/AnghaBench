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

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct radio_isa_card* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct radio_isa_card *rtrack2_alloc(void)
{
	return kzalloc(sizeof(struct radio_isa_card), GFP_KERNEL);
}