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
struct attribute {char* name; int /*<<< orphan*/  mode; } ;
struct hw_stats_attribute {int index; struct attribute attr; int /*<<< orphan*/  port_num; int /*<<< orphan*/ * store; int /*<<< orphan*/  show; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  S_IRUGO ; 
 struct hw_stats_attribute* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_hw_stats ; 

__attribute__((used)) static struct attribute *alloc_hsa(int index, u8 port_num, const char *name)
{
	struct hw_stats_attribute *hsa;

	hsa = kmalloc(sizeof(*hsa), GFP_KERNEL);
	if (!hsa)
		return NULL;

	hsa->attr.name = (char *)name;
	hsa->attr.mode = S_IRUGO;
	hsa->show = show_hw_stats;
	hsa->store = NULL;
	hsa->index = index;
	hsa->port_num = port_num;

	return &hsa->attr;
}