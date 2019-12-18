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
struct attribute {char* name; int mode; } ;
struct hw_stats_attribute {struct attribute attr; int /*<<< orphan*/  port_num; scalar_t__ index; int /*<<< orphan*/  store; int /*<<< orphan*/  show; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 struct hw_stats_attribute* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_stats_lifespan ; 
 int /*<<< orphan*/  show_stats_lifespan ; 

__attribute__((used)) static struct attribute *alloc_hsa_lifespan(char *name, u8 port_num)
{
	struct hw_stats_attribute *hsa;

	hsa = kmalloc(sizeof(*hsa), GFP_KERNEL);
	if (!hsa)
		return NULL;

	hsa->attr.name = name;
	hsa->attr.mode = S_IWUSR | S_IRUGO;
	hsa->show = show_stats_lifespan;
	hsa->store = set_stats_lifespan;
	hsa->index = 0;
	hsa->port_num = port_num;

	return &hsa->attr;
}