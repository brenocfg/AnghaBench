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
struct seq_file {struct l2t_data* private; } ;
struct l2t_data {size_t l2t_size; void* l2tab; } ;
typedef  size_t loff_t ;

/* Variables and functions */

__attribute__((used)) static inline void *l2t_get_idx(struct seq_file *seq, loff_t pos)
{
	struct l2t_data *d = seq->private;

	return pos >= d->l2t_size ? NULL : &d->l2tab[pos];
}