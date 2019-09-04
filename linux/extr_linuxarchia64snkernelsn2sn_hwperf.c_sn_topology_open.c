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
struct sn_hwperf_object_info {int dummy; } ;
struct seq_file {struct sn_hwperf_object_info* private; } ;
struct inode {int dummy; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 
 int sn_hwperf_enum_objects (int*,struct sn_hwperf_object_info**) ; 
 int /*<<< orphan*/  sn_topology_seq_ops ; 

int sn_topology_open(struct inode *inode, struct file *file)
{
	int e;
	struct seq_file *seq;
	struct sn_hwperf_object_info *objbuf;
	int nobj;

	if ((e = sn_hwperf_enum_objects(&nobj, &objbuf)) == 0) {
		e = seq_open(file, &sn_topology_seq_ops);
		seq = file->private_data;
		seq->private = objbuf;
	}

	return e;
}