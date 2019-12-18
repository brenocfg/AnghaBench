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
struct inode {int dummy; } ;
struct file {struct aspeed_p2a_user* private_data; } ;
struct aspeed_p2a_user {struct aspeed_p2a_user* parent; int /*<<< orphan*/  readwrite; scalar_t__ read; struct file* file; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct aspeed_p2a_user* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aspeed_p2a_open(struct inode *inode, struct file *file)
{
	struct aspeed_p2a_user *priv;

	priv = kmalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->file = file;
	priv->read = 0;
	memset(priv->readwrite, 0, sizeof(priv->readwrite));

	/* The file's private_data is initialized to the p2a_ctrl. */
	priv->parent = file->private_data;

	/* Set the file's private_data to the user's data. */
	file->private_data = priv;

	return 0;
}