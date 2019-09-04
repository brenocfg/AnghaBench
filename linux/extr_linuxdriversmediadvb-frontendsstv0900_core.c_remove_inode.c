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
struct stv0900_internal {int /*<<< orphan*/  i2c_addr; int /*<<< orphan*/  i2c_adap; } ;
struct stv0900_inode {struct stv0900_inode* next_inode; } ;

/* Variables and functions */
 struct stv0900_inode* find_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct stv0900_inode*) ; 
 struct stv0900_inode* stv0900_first_inode ; 

__attribute__((used)) static void remove_inode(struct stv0900_internal *internal)
{
	struct stv0900_inode *prev_node = stv0900_first_inode;
	struct stv0900_inode *del_node = find_inode(internal->i2c_adap,
						internal->i2c_addr);

	if (del_node != NULL) {
		if (del_node == stv0900_first_inode) {
			stv0900_first_inode = del_node->next_inode;
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