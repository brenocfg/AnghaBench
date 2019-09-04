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
struct hypfs_dbfs_file {int dummy; } ;
struct hypfs_dbfs_data {struct hypfs_dbfs_file* dbfs_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hypfs_dbfs_data* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hypfs_dbfs_data *hypfs_dbfs_data_alloc(struct hypfs_dbfs_file *f)
{
	struct hypfs_dbfs_data *data;

	data = kmalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return NULL;
	data->dbfs_file = f;
	return data;
}