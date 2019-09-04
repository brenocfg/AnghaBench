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
struct stv0900_internal {int dummy; } ;
struct stv0900_inode {struct stv0900_inode* next_inode; struct stv0900_internal* internal; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct stv0900_inode* stv0900_first_inode ; 

__attribute__((used)) static struct stv0900_inode *append_internal(struct stv0900_internal *internal)
{
	struct stv0900_inode *new_node = stv0900_first_inode;

	if (new_node == NULL) {
		new_node = kmalloc(sizeof(struct stv0900_inode), GFP_KERNEL);
		stv0900_first_inode = new_node;
	} else {
		while (new_node->next_inode != NULL)
			new_node = new_node->next_inode;

		new_node->next_inode = kmalloc(sizeof(struct stv0900_inode),
								GFP_KERNEL);
		if (new_node->next_inode != NULL)
			new_node = new_node->next_inode;
		else
			new_node = NULL;
	}

	if (new_node != NULL) {
		new_node->internal = internal;
		new_node->next_inode = NULL;
	}

	return new_node;
}