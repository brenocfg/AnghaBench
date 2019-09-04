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
struct fpga_internal {int /*<<< orphan*/  dev; } ;
struct fpga_inode {struct fpga_inode* next_inode; } ;

/* Variables and functions */
 struct fpga_inode* find_inode (int /*<<< orphan*/ ) ; 
 struct fpga_inode* fpga_first_inode ; 
 int /*<<< orphan*/  kfree (struct fpga_inode*) ; 

__attribute__((used)) static void remove_inode(struct fpga_internal *internal)
{
	struct fpga_inode *prev_node = fpga_first_inode;
	struct fpga_inode *del_node = find_inode(internal->dev);

	if (del_node != NULL) {
		if (del_node == fpga_first_inode) {
			fpga_first_inode = del_node->next_inode;
		} else {
			while (prev_node->next_inode != del_node)
				prev_node = prev_node->next_inode;

			if (del_node->next_inode == NULL)
				prev_node->next_inode = NULL;
			else
				prev_node->next_inode =
					prev_node->next_inode->next_inode;
		}

		kfree(del_node);
	}
}