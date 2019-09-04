#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rftype {int flags; } ;
struct kernfs_open_file {TYPE_1__* kn; } ;
struct TYPE_2__ {struct rftype* priv; } ;

/* Variables and functions */
 int RFTYPE_FLAGS_CPUS_LIST ; 

__attribute__((used)) static bool is_cpu_list(struct kernfs_open_file *of)
{
	struct rftype *rft = of->kn->priv;

	return rft->flags & RFTYPE_FLAGS_CPUS_LIST;
}